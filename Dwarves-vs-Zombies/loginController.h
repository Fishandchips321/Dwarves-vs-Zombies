#pragma once
#include <string>
#include "loginNetController.h"
class loginController
{
public:
	loginController();
	static bool login(std::string username, std::string password);
	static bool renewToken();
	static bool logout();
	~loginController();

	static std::string username;
	static std::string loginToken;
	static bool loggedIn;

	enum class errors
	{
		NONE,
		BAD_LOGIN,
		BANNED,
		IP_BANNED,
		LOGIN_TIME_OUT,
		PACKET_MALFORMED,
		NO_REPLY
	};

	errors error;
};

