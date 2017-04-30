#include "console.h"



console::console()
{
	renderer = windowController::registerWindow(150, 75, "Console");

	Rcout = consoleController::rebindCout();
	Rclog = consoleController::rebindClog();
	Rcerr = consoleController::rebindCerr();
}

void console::update()
{
}

void console::eventUpdate()
{
}

void console::draw()
{
}


console::~console()
{
}
