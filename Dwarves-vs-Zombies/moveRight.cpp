#include "moveRight.h"



moveRight::moveRight()
{
}

void moveRight::keyIsDown()
{
	SDL_Event *ev = new SDL_Event;
	ev->type = eventController::playerEvent;
	ev->user.code = eventController::moveRight;
	SDL_PushEvent(ev);
}


moveRight::~moveRight()
{
}
