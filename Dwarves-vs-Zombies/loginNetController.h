#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <queue>
#include "counter.h"

using boost::asio::ip::tcp;

class loginNetController
{
public:
	loginNetController();
	bool sendMessage(std::string message);
	std::string getMessage();
	~loginNetController();

private:
	boost::asio::io_service io_service;
	tcp::socket socket;
	tcp::resolver::iterator endpoint;
	const std::string loginServerIP = "", loginServerPort = "";
	boost::thread recThread;
	boost::mutex recLock;
	boost::mutex sockLock;
	std::queue<std::string> recieved;
	bool connected;
	counter timer;

	void reciever();

};

