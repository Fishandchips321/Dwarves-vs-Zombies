#include "walk.h"



walk::walk()
{
}

void walk::keyIsDown()
{
	SDL_Event *ev = new SDL_Event;
	ev->type = eventController::playerEvent;
	ev->user.code = eventController::walk;
	SDL_PushEvent(ev);
}


walk::~walk()
{
}
