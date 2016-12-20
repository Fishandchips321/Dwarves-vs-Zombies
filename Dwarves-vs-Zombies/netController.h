#pragma once
#include <string>
#include <vector>
#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "boost/array.hpp"
#include "resources.h"
#include "eventController.h"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

class netController
{
public:
	netController();
	static bool connect(std::string address);
	static void update();
	static void eventUpdate();
	static void send(std::string data);
	~netController();

private:
	static void netSenderThread();
	static void netRecieverThread();

	static boost::asio::io_service io_service;
	static boost::thread sendThread;
	static boost::thread recieveThread;
	static udp::endpoint UDPEndpoint;
	static udp::socket USocket;
	static boost::mutex USLock;

	static const std::string port;
	static bool disconnect;
	static bool connected;
	static std::vector<std::string> recieved;
	static std::vector<std::string> toSend;
};

