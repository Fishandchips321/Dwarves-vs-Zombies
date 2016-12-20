#include "netController.h"

boost::asio::io_service netController::io_service; //the IO service
udp::socket netController::USocket(io_service); //the socket used to communicate with the server
udp::endpoint netController::UDPEndpoint; //the object used to determin the destination of the packets
bool netController::disconnect = false; //whether the threads should end (only set to true when the object gets destroyed
bool netController::connected = false; //whether a server session is active
const std::string netController::port = "37568"; //the port number of the server
boost::thread netController::sendThread(netController::netSenderThread); //the thread object for the sender thread
boost::thread netController::recieveThread(netController::netRecieverThread); //the thread object for the reciever object
std::vector<std::string> netController::recieved; //holds everything that has been recieved and not parsed
boost::mutex netController::USLock;
std::vector<std::string> netController::toSend;


netController::netController()
{
}

bool netController::connect(std::string address)
{
	try //connect to the address and verify server identity
	{
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(address, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		std::string message = "ping";

		boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

		boost::array<char, 128> buf;
		boost::system::error_code error;

		size_t len = socket.read_some(boost::asio::buffer(buf), error);
		
		if (error && error != boost::asio::error::eof)
			throw boost::system::system_error(error);

		if (buf.data() != "pong")
		{
			std::cout << "[WARN]: server response unexpected. Not connected." << std::endl;
			return false;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "[ERROR]: An error occurred while trying to connect to server " << address << ". Error: " << e.what() << std::endl;
		return false;
	}

	//setup UDP networking
	
	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), address, port);
	UDPEndpoint = *resolver.resolve(query);

	USocket.open(udp::v4());

	connected = true;

	return true;
}

void netController::update()
{
	
}

void netController::eventUpdate()
{
	if (resources::currentEvent->type == eventController::disconnectNet)
	{
		disconnect = true;
	}
}

void netController::send(std::string data)
{

}

void netController::netSenderThread()
{
	while (true)
	{
		if (connected)
		{
			if (toSend.size() != 0)
			{
				toSend.rbegin();
				USLock.lock();
				USocket.send_to(boost::asio::buffer(toSend), UDPEndpoint);
				USLock.unlock();
			}
		}

		if (disconnect)
			break;
	}
}

void netController::netRecieverThread()
{
	while (true)
	{
		if (connected)
		{
			boost::array<char, 128> recv_buf;
			USLock.lock();
			size_t len = USocket.receive_from(boost::asio::buffer(recv_buf), UDPEndpoint);
			USLock.unlock();
			recieved.push_back(recv_buf.data());
		}

		if (disconnect)
			break;
	}
}


netController::~netController()
{
	connected = false;
	disconnect = true;
	sendThread.join();
	recieveThread.join();
}
