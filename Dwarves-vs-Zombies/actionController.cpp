#include "actionController.h"

action* actionController::actions[maxActions];

actionController::actionController()
{
}

bool actionController::registerAction(action *a, SDL_Keycode key, int action)
{
	for (size_t x = 0; x < maxActions; x++)
	{
		if (actions[x]->key == key)
		{
			return false;
		}
	}

	a->key = key;
	actions[action] = a;
	return true;
}

bool actionController::rebindAction(int action, SDL_Keycode key)
{
	if(action > maxActions)
		return false;

	actions[action]->key = key;
	return true;
}

void actionController::eventUpdate()
{
	if (UIController::getFocus() != 0)
	{
		if (eventController::currentEvent.type == SDL_KEYDOWN)
		{
			for (size_t x = 0; x < maxActions; x++)
			{
				if (actions[x]->key == eventController::currentEvent.key.keysym.sym)
				{
					actions[x]->keyDown();
					break;
				}
			}
		}

		if (eventController::currentEvent.type == SDL_KEYUP)
		{
			for (size_t x = 0; x < maxActions; x++)
			{
				if (actions[x]->key == eventController::currentEvent.key.keysym.sym)
				{
					actions[x]->keyUp();
					break;
				}
			}
		}
	}
}

actionController::~actionController()
{
	for (int x = 0; x < maxActions; x++)
	{
		delete actions[x];
	}
}
