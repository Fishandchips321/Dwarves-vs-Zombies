#include "netController.h"
#include <boost/array.hpp>
#include <boost/regex.hpp>
#include <memory>
#include "eventController.h"

boost::asio::io_service netController::io_service; //the IO service
udp::socket netController::USocket(io_service); //the socket used to communicate with the server
udp::endpoint netController::UDPEndpoint; //the object used to determin the destination of the packets
bool netController::connected = false; //whether a server session is active
const std::string netController::port = "37568"; //the port number of the server
boost::mutex netController::USLock; //mutex for the UDP socket
int netController::netID; //the ID that the server gives the client
std::string netController::currentMessage; //the current game message
netController::nState netController::state; //the state of the net controller
boost::thread netController::gameSendThread, netController::gameRecieveThread, netController::controlSendThread, netController::controlRecieveThread; //the threads for the control and game net
tcp::resolver::iterator netController::endpoint_iterator; //destination of TCP socket
tcp::socket netController::TSocket(io_service); //TCP socket used for control messages
boost::mutex netController::TSLock; //mutex for TCP socket
std::queue<netController::netMessage> netController::controlRecieved; //recieved control messages
std::queue<std::string> netController::controlToSend; //control messages to be sent
std::queue<std::string> netController::gameRecieved; //game messages recieved
std::queue<std::string> netController::gameToSend; //game messages to be sent
netController::netMessage netController::currentControlMessage; //current control message
boost::mutex netController::controlRecLock; //mutex for controlRecieved
boost::mutex netController::controlSendLock; //mutex for controlToSend
boost::mutex netController::gameRecLock; //mutex for gameRecieved
boost::mutex netController::gameSendLock; //mutex for gameToSend
counter netController::keepaliveTimer; //how long ago the last packet was sent. if it reaches 5 seconds a keepalive ping is sent to the server to make sure the client is still connected
bool netController::keepaliveSent; //whether the client is waiting for a keepalive response packet from the server

netController::netController()
{
	state = nState::DISCONNECTED;
	netID = -1;
}

std::vector<std::string> netController::splitString(std::string to_split)
{
	//source: https://www.quora.com/How-do-I-split-a-string-by-space-into-an-array-in-c++/answer/Grzegorz-Go%C5%82da?srid=tzNb&share=73558a3a
	std::vector<std::string> array;
	std::size_t pos = 0, found;
	while ((found = to_split.find_first_of(' ', pos)) != std::string::npos) {
		array.push_back(to_split.substr(pos, found - pos));
		pos = found + 1;
	}
	array.push_back(to_split.substr(pos));

	return array;
}

bool netController::connect(std::string address)
{
	state = nState::CONNECTING;
	try //connect to the address and verify server identity
	{
		//setup the TCP endpoint with the server address
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(address, port);
		endpoint_iterator = resolver.resolve(query);
		//connect to the server through TCP
		boost::asio::connect(TSocket, endpoint_iterator);
		//send a ping to the server to test if the server is responding/responding correctly
		std::string message = "ping";

		boost::system::error_code ignored_error;//an error code that is ignored as some overloads of boost::asio::write just throw errors instead of using this data structure
		boost::asio::write(TSocket, boost::asio::buffer(message), ignored_error);//send the "ping" message
		//setup containers to recieve the message
		boost::array<char, 128> buf;
		boost::system::error_code error;
		
		size_t len = TSocket.read_some(boost::asio::buffer(buf), error);//get the message
		//if the error code isn't end of file, throw it
		if (error && error != boost::asio::error::eof)
			throw boost::system::system_error(error);
		//if the recieved message isn't "pong" then the server didn't respond correctly (or at all) so return false
		if (buf.data() != "pong")
		{
			std::cout << "[WARN]: server response unexpected. Not connected." << std::endl;
			return false;
		}
	}
	catch (std::exception& e) //if an exception was thrown
	{
		std::cout << "[ERROR]: An error occurred while trying to connect to server " << address << ". Error: " << e.what() << std::endl; //output error message
		state = nState::ERROR_CONNECTING; //set the state
		return false; //the connect was not successful
	}

	//setup UDP connection
	
	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), address, port);
	UDPEndpoint = *resolver.resolve(query);
	//^^ setup UDP connection containers (endpoint)
	USocket.open(udp::v4()); //open the UDP socket
	//the program is connected to the server and can start communicating
	connected = true;
	state = nState::CONNECTED;
	//setup the send/recieve threads for TCP/UDP
	gameSendThread = boost::thread(netGameSend);
	gameRecieveThread = boost::thread(netGameRecieve);
	controlSendThread = boost::thread(netControlSend);
	controlRecieveThread = boost::thread(netControlRecieve);
	keepaliveTimer.start();

	return true; //the connect was successful
}

void netController::connectUDP()
{

}

void netController::update()
{
	switch(state)
	{
	case nState::DISCONNECTED:
		break;
	case nState::CONNECTING:
		//wait for the server to tell us to send a UDP message
		break;
	case nState::CONNECTED:
		//wait for the server to request authentication
		if (currentControlMessage.NCM == AUTHENTICATE)
		{
			state = nState::AUTHENTICATING;
		}

		break;
	case nState::AUTHENTICATING:
		//send the login token to the game server
		sendControl(std::to_string(AUTHENTICATE) + loginController::loginToken);
		state = nState::AUTHREPLY;

		break;
	case nState::AUTHREPLY:
		//wait for the server to reply with a user ID
		if (currentControlMessage.NCM == USER_ID)
		{
			if (currentControlMessage.paramaters == "-1") //if auth failed, the user ID will be -1
			{
				eventController::sendEvent(eventController::authError); //send an event to notify of the error
				sendControl(std::to_string(DISCONNECT));//tell the server that we are terminating the connection
				state = nState::DISCONNECTING;
			}
			else
			{
				netID = stoi(currentControlMessage.paramaters); //set the net ID
				state = nState::SEND_USER_DATA;
			}
		}

		break;
	case nState::SEND_USER_DATA:

		sendControl(std::to_string(USER_ID) + loginController::username);//send the game server the player's username
		state = nState::LOBBY;

		break;
	case nState::LOBBY:
		if (currentControlMessage.NCM == LOBBY_PLAYER_UPDATE)
			updateLobby();
		break;
	case nState::LOAD_GAME:
		break;
	case nState::PLAY_GAME:
		updateGame();
		break;
	case nState::GAME_END:
		break;
	case nState::DISCONNECTING:

		if (currentControlMessage.NCM == DISCONNECT)//if the server replies to our request to disconnect
		{
			//set the states to disconnected
			state = nState::DISCONNECTED;
			connected = false;
			TSocket.close();//close the TCP socket
		}

		break;
	case nState::QUICK_DISCONNECT:
		send(std::to_string(QUICK_DISCONNECT)); //tell the game server that we are going to quick disconnect via UDP
		//set the states to disconnected
		connected = false;
		state = nState::DISCONNECTED;
		TSocket.close();//close the TCP socket
		break;
	}

	if (keepaliveTimer.getTicks() >= 5000)//if a message hasn't been sent for 5 seconds, send a keepalive ping message
	{
		sendControl(KEEPALIVE_PING);//send keepalive ping
		keepaliveSent = true;//expect a keepalive pong reply
		keepaliveTimer.restart();//reset the counter
	}

	if (keepaliveSent && currentControlMessage.NCM == KEEPALIVE_PONG)//if a keepalive ping message has been sent and the current control message is a keepalive pong reply
	{
		keepaliveSent = false;//the keepalive pong has been recieved
	}

	if (currentControlMessage.NCM == KEEPALIVE_PING) //if the server sent a keepalive ping, reply with a keepalive pong
	{
		sendControl(KEEPALIVE_PONG);
		keepaliveTimer.restart();
	}
}

void netController::updateLobby()
{
	std::vector<std::string> data = splitString(currentControlMessage.paramaters);//the different paramaters
	int action = atoi(data[0].c_str());//get the lobby control action
	std::shared_ptr<int> playerID(new int), playerClass(new int);
	std::shared_ptr<std::string> playerUsername(new std::string);
	SDL_Event* e;
	SDL_memset(&e, 0, sizeof(e));//clear the memory of the event container

	e->type = eventController::lobbyPlayerUpdate;//set the event type to the lobby player update event

	switch (action)
	{
	case 0://player connected

		*playerID = atoi(data[1].c_str());//get the player ID
		*playerUsername = data[2];//get the player's username
		//store the pointers in the event container
		e->user.data1 = playerID.get();
		e->user.data2 = playerUsername.get();

		break;
	case 1://player change class

		*playerID = atoi(data[1].c_str());//get the player ID
		*playerClass = atoi(data[3].c_str());//get the class ID
		//store the pointers in the event container
		e->user.data1 = playerID.get();
		e->user.data2 = playerClass.get();

		break;
	case 2://player disconnected

		*playerID = atoi(data[1].c_str());//get the player ID

		e->user.data1 = &playerID;//store the pointer in the event container

		break;
	}

	SDL_PushEvent(e);//push the event
}

void netController::updateGame()
{
	SDL_Event* e;
	SDL_memset(&e, 0, sizeof(e));
	std::shared_ptr<eventController::playerSpawn> player(new eventController::playerSpawn);
	std::vector<std::string> data = splitString(currentControlMessage.paramaters);

	e->type = eventController::spawnPlayer; //set the event

	switch (currentControlMessage.NCM)
	{
	case PLAYER_SPAWN:

		player->playerID = atoi(data[0].c_str());//get the player ID
		player->playerClass = atoi(data[1].c_str());//get the player class ID
		player->x = atoi(data[2].c_str());//get the player's X spawn pos
		player->y = atoi(data[3].c_str());//get the player's Y spawn pos

		e->user.data1 = &player;//store the pointer of the player spawn data container in the event container

		break;
	}
	SDL_PushEvent(e);//push the event
}

void netController::eventUpdate()
{
	//if the game requests to disconnect from the server, set the state to disconnecting
	if (eventController::currentEvent.type == eventController::disconnectNet)
	{
		sendControl(std::to_string(DISCONNECT));
		state = nState::DISCONNECTING;
	}
	//if the game needs to exit quickly, set the state to quick disconnect
	if (eventController::currentEvent.type == eventController::quickExit)
	{
		state = nState::QUICK_DISCONNECT;
	}
}

void netController::send(std::string data)//send a game message
{
	//get a timestamp object
	boost::posix_time::ptime now;
	now = boost::posix_time::microsec_clock::universal_time();
	//send constructed message
	gameSendLock.lock();
	gameToSend.push(boost::posix_time::to_simple_string(now) + " " + std::to_string(netID) + " " + data);
	gameSendLock.unlock();
	keepaliveTimer.restart();
}

bool netController::nextMessage()//get the next game message recieved
{
	if (gameRecieved.size() == 0) //if the queue is empty, return false
		return false;
	currentMessage = gameRecieved.front();//get the next message in the queue
	gameRecieved.pop();//remove the message from the queue
	return true;
}

void netController::sendControl(std::string data)
{
	//get a timestamp object
	boost::posix_time::ptime now;
	now = boost::posix_time::microsec_clock::universal_time();
	//send the constructed message
	controlSendLock.lock();
	controlToSend.push(boost::posix_time::to_simple_string(now) + " " + std::to_string(netID) + " " + data);
	controlSendLock.unlock();
	keepaliveTimer.restart();
}

void netController::sendControl(int ncm, std::string params)
{
	//get a timestamp
	boost::posix_time::ptime now;
	now = boost::posix_time::microsec_clock::universal_time();
	//send the constructed message
	controlSendLock.lock();
	controlToSend.push(boost::posix_time::to_simple_string(now) + " " + std::to_string(netID) + " " + std::to_string(ncm) + " " + params);
	controlSendLock.unlock();
	keepaliveTimer.restart();
}

void netController::sendControl(netMessage message)
{
	//get a timestamp
	boost::posix_time::ptime now;
	now = boost::posix_time::microsec_clock::universal_time();

	if (message.completeMessage == "")//if the complete message field is empty
	{
		//send the constructed message
		controlSendLock.lock();
		controlToSend.push(boost::posix_time::to_simple_string(now) + " " + std::to_string(netID) + " " + std::to_string(message.NCM) + " " + message.paramaters);
		controlSendLock.unlock();
	}
	else //if there is a complete message, use it
	{
		//send the constructed message
		controlSendLock.lock();
		controlToSend.push(boost::posix_time::to_simple_string(now) + " " + std::to_string(netID) + " " + message.completeMessage);
		controlSendLock.unlock();
	}
	keepaliveTimer.restart();
}

bool netController::nextControlMessage()
{
	if (controlRecieved.size() == 0)//if the queue is empty, return false
		return false;
	currentControlMessage = controlRecieved.front();//get the next message in the queue
	controlRecieved.pop();//remove the message from the queue
	return true;
}

void netController::netControlSend()
{
	while (connected)
	{
		if (controlToSend.size() != 0) //if there is something to send
		{
			for (size_t x = 0; x < controlToSend.size(); x++)//send each message in the queue
			{
				controlSendLock.lock();
				std::string send = controlToSend.front();//get the next message to be sent
				controlToSend.pop();//remove the message from the queue
				controlSendLock.unlock();

				boost::system::error_code ignored_error;
				TSLock.lock();
				boost::asio::write(TSocket, boost::asio::buffer(send), ignored_error); //send the message
				TSLock.unlock();
			}
		}
	}
}

void netController::netControlRecieve()
{
	while (connected)
	{
		//setup containers to recieve the message
		boost::array<char, 128> buf;
		boost::system::error_code error;
		netMessage message; //the container for the message
		//read a message (will wait for a message)
		TSLock.lock();
		boost::asio::read(TSocket, boost::asio::buffer(buf));
		TSLock.unlock();
		//format the message into the message container
		message.completeMessage = buf.data(); //store the complete message
		message.timestamp = boost::posix_time::time_from_string(message.completeMessage.substr(0, 23)); //get the timestamp from the front of the message

		boost::smatch what;//container for boost::regex_search findings
		boost::regex_search(message.completeMessage, what, boost::regex("\\s[0-9]*\\s")); //search for the network control message
		message.NCM = atoi(what[0].str().c_str()); //store the network control message
		//store the paramaters at the end of the message
		if (message.NCM > 9)//if there are 2 characters for the NCM
			message.paramaters = message.completeMessage.substr(28, message.completeMessage.size() - 28);
		else//if there is 1 character for the NCM
			message.paramaters = message.completeMessage.substr(27, message.completeMessage.size() - 27);
		//store the message
		controlRecLock.lock();
		controlRecieved.push(message);
		controlRecLock.unlock();
	}
}

void netController::netGameSend()
{
	while (connected) //thread loop while connected
	{
		if (gameToSend.size() != 0) //if there is something to send
		{
			for (size_t x = 0; x < gameToSend.size(); x++) //loop through each message to be sent
			{
				gameSendLock.lock();
				std::string send = gameToSend.front(); //get the next string to send
				gameToSend.pop();//remove it from the vector
				gameSendLock.unlock();

				USLock.lock();
				USocket.send_to(boost::asio::buffer(send), UDPEndpoint); //send the message to the server
				USLock.unlock();
			}
		}
	}
}

void netController::netGameRecieve()
{
	while (connected)
	{
		boost::array<char, 128> recv_buf; //the container for the message
		USLock.lock();
		size_t len = USocket.receive_from(boost::asio::buffer(recv_buf), UDPEndpoint); //waits for a message to be recieved
		USLock.unlock();

		
		std::string message = recv_buf.data(); //get the message into a string for ease of use

		gameRecLock.lock();
		gameRecieved.push(message); //add the message to the queue
		gameRecLock.unlock();
	}
}

netController::~netController()
{
	connected = false;
	state = nState::DISCONNECTED;

	TSocket.close();

	//stop the recieving threads as they will not stop on their own (won't continue the loop without recieving a message)
	gameRecieveThread.interrupt();
	controlRecieveThread.interrupt();
	//wait for the sending threads to exit
	controlSendThread.join();
	gameSendThread.join();
}
