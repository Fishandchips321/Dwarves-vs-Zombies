#include "moveLeft.h"



moveLeft::moveLeft()
{
}

void moveLeft::keyIsDown()
{
	SDL_Event *ev = new SDL_Event;
	ev->type = eventController::playerEvent;
	ev->user.code = eventController::moveForward;
	SDL_PushEvent(ev);
}


moveLeft::~moveLeft()
{
}
