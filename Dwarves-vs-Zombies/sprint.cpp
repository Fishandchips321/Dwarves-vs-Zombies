#include "sprint.h"



sprint::sprint()
{
}

void sprint::keyIsDown()
{
	SDL_Event *ev = new SDL_Event;
	ev->type = eventController::playerEvent;
	ev->user.code = eventController::sprint;
	SDL_PushEvent(ev);
}


sprint::~sprint()
{
}
