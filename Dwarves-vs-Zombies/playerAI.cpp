#include "playerAI.h"



playerAI::playerAI()
{
}

void playerAI::update()
{
}

void playerAI::eventUpdate()
{
	if (eventController::currentEvent.type == eventController::playerEvent)
	{
		switch (eventController::currentEvent.user.code)
		{
		case eventController::moveForward:
			ent->entityRect.y -= ent->movVel;
			break;

		case eventController::moveBack:
			ent->entityRect.y += ent->movVel;
			break;
			
		case eventController::moveLeft:
			ent->entityRect.x -= ent->movVel;
			break;

		case eventController::moveRight:
			ent->entityRect.x += ent->movVel;
			break;

		case eventController::walk:
			ent->movVel = ent->walkVel;
			break;
			
		case eventController::sprint:
			ent->movVel = ent->sprintVel;
			break;

		case eventController::run:
			ent->movVel = ent->runVel;
			break;
		}
	}
}

void playerAI::netUpdate()
{
}


playerAI::~playerAI()
{
}
