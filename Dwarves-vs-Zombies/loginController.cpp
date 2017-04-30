#include "loginController.h"

std::string loginController::username;
std::string loginController::loginToken;
bool loginController::loggedIn;

loginController::loginController()
{
	loggedIn = false;
	username = "";
	loginToken = "";
}

bool loginController::login(std::string username, std::string password)
{
	loginNetController net;
	net.sendMessage("LOGIN " + username + " " + password);
	std::string status = net.getMessage();
	if (status.find("LOGIN"))
	{
		if (status.substr(7) == "1")
		{
			loginController::username = username;
			loginToken = status.substr(9, status.size() - 9);
			return true;
		}
	}
	return false;
}

bool loginController::renewToken()
{
	loginNetController net;
	net.sendMessage("RENEWTOKEN " + loginToken);
	std::string status = net.getMessage();
	if (status.find("LOGIN"))
	{
		if (status.substr(7) == "1")
		{
			loginToken = status.substr(9, status.size() - 9);
			return true;
		}
	}
	return false;
}

bool loginController::logout()
{
	loginNetController net;
	net.sendMessage("LOGOUT " + loginToken);
	std::string status = net.getMessage();
	if (status.find("OF"))
	{
		return true;
	}
	return false;
}


loginController::~loginController()
{
}
