#include "consoleController.h"

std::streambuf* consoleController::oldCoutStreamBuf;
std::streambuf* consoleController::oldCerrStreamBuff;
std::streambuf* consoleController::oldClogStreamBuf;

consoleController::consoleController()
{
}

std::ostringstream* consoleController::rebindCout()
{
	oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream* strCout = new std::ostringstream;
	std::cout.rdbuf(strCout->rdbuf());


	return strCout;
}

std::ostringstream * consoleController::rebindClog()
{
	oldCoutStreamBuf = std::clog.rdbuf();
	std::ostringstream* strClog = new std::ostringstream;
	std::clog.rdbuf(strClog->rdbuf());


	return strClog;
}

std::ostringstream * consoleController::rebindCerr()
{
	oldCoutStreamBuf = std::cerr.rdbuf();
	std::ostringstream* strCerr = new std::ostringstream;
	std::cerr.rdbuf(strCerr->rdbuf());


	return strCerr;
}

bool consoleController::resetConsole()
{
	std::cout.rdbuf(oldCoutStreamBuf);

	if (std::cout.rdbuf() == oldCoutStreamBuf)
		return true;
	else
		return false;
}


consoleController::~consoleController()
{
}
