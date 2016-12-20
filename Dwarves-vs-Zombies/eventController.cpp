#include "eventController.h"

eventController::eventController()
{

}

bool eventController::init()
{
	Uint32 myEventType = SDL_RegisterEvents(1);
	if (myEventType != ((Uint32)-1))
		return true;
	else
		return false;
}


eventController::~eventController()
{
}
