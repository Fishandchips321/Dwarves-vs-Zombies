#include "moveForward.h"



moveForward::moveForward()
{
}

void moveForward::keyIsDown()
{
	SDL_Event *ev = new SDL_Event;
	ev->type = eventController::playerEvent;
	ev->user.code = eventController::moveForward;
	SDL_PushEvent(ev);
}

moveForward::~moveForward()
{
}
