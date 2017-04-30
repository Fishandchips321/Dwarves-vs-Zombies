#include "loginNetController.h"



loginNetController::loginNetController()
	:socket(io_service)
{
	//setup the endpoint
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(loginServerIP, loginServerPort);
	endpoint = resolver.resolve(query);

	boost::asio::connect(socket, endpoint);//connect to the login server
	
	if (sendMessage("ping"))
	{
		//if the response is correct, set the state to connected
		if (getMessage() == "pong")
		{
			connected = true;
			recThread = boost::thread(boost::bind(&loginNetController::reciever, this)); //start the thread
		}
	}
}

bool loginNetController::sendMessage(std::string message)
{
	try
	{
		boost::system::error_code ignored_error;//an error code that is ignored as some overloads of boost::asio::write just throw errors
		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);//send the "ping" message
	}
	catch (std::exception& e)
	{
		std::cout << "[ERROR]: Couldn't send login message \"" << message << "\". Exception: \"" << e.what() << "\"" << std::endl;
		return false;
	}
	return true;
}

std::string loginNetController::getMessage()
{
	counter timer;
	timer.start();

	while (recieved.size() == 0)
	{
		if (timer.getTicks() == 5000)
		{
			timer.stop();
			break;
		}
	}

	if (recieved.size() > 0) //if there is a message in the queue
	{
		std::string message = recieved.front(); //get the message
		recieved.pop();//remove the message from the queue
		return message;
	}
	return "";
}


loginNetController::~loginNetController()
{
	socket.close();
	connected = false;
}

void loginNetController::reciever()
{
	while (connected)
	{
		//setup containers to recieve the message
		boost::array<char, 128> buf;
		boost::system::error_code error;
		std::string message;
							//read a message (will wait for a message)
		sockLock.lock();
		boost::asio::read(socket, boost::asio::buffer(buf));
		sockLock.unlock();

		message = buf.data();

		recLock.lock();
		recieved.push(message);
		recLock.unlock();
	}
}
