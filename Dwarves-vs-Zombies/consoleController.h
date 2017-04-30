#pragma once
#include <iostream>
#include <sstream>
class consoleController
{
public:
	consoleController();
	static std::ostringstream* rebindCout();
	static std::ostringstream* rebindClog();
	static std::ostringstream* rebindCerr();
	static bool resetConsole();
	~consoleController();

private:
	static std::streambuf* oldCoutStreamBuf;
	static std::streambuf* oldCerrStreamBuff;
	static std::streambuf* oldClogStreamBuf;
};

