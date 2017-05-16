#include "moveBackward.h"



moveBackward::moveBackward()
{
}

void moveBackward::keyIsDown()
{
	SDL_Event *ev = new SDL_Event;
	ev->type = eventController::playerEvent;
	ev->user.code = eventController::moveBack;
	SDL_PushEvent(ev);
}

moveBackward::~moveBackward()
{
}
