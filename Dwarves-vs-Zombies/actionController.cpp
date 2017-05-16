#include "actionController.h"

action* actionController::actions[maxActions];

actionController::actionController()
{
}

bool actionController::registerAction(action *a, SDL_Keycode key, int action)
{
	if (action > maxActions) //if the number passed is greater than the number of actions, return false
		return false;

	//if an action already reacts to the keycode, return false
	for (size_t x = 0; x < maxActions; x++)
	{
		if (actions[x]->key == key)
		{
			return false;
		}
	}
	//set the key in the action and put it into the array
	a->key = key;
	actions[action] = a;
	return true;
}

bool actionController::rebindAction(int action, SDL_Keycode key)
{
	if(action > maxActions) //if the number passed is greater than the number of actions, return false
		return false;

	actions[action]->key = key; //change the key that the action reacts to
	return true;
}

void actionController::eventUpdate()
{
	if (UIController::getFocus() != 0) //if there isn't a menu present
	{
		if (eventController::currentEvent.type == SDL_KEYDOWN) //when a key is pressed down
		{
			for (size_t x = 0; x < maxActions; x++) //find the first action with the same key code
			{
				if (actions[x]->key == eventController::currentEvent.key.keysym.sym) //if the action's key matches the depressed key, call the keyDown function
				{
					actions[x]->keyDown();
					break;
				}
			}
		}

		if (eventController::currentEvent.type == SDL_KEYUP) //when a key is released
		{
			for (size_t x = 0; x < maxActions; x++)//find the first action with the same key code
			{
				if (actions[x]->key == eventController::currentEvent.key.keysym.sym)//if the action's key matches the depressed key, call the keyUp function
				{
					actions[x]->keyUp();
					break;
				}
			}
		}

		const Uint8* keyStates = SDL_GetKeyboardState(nullptr); //get the states of every key

		for (int x = 0; x < maxActions; x++) //loop through every action
		{
			if (keyStates[actions[x]->key]) //if the key is pressed down
			{
				actions[x]->keyIsDown();
			}
		}

		if (eventController::currentEvent.type == SDL_MOUSEBUTTONDOWN) //when a mouse button is pressed
		{
			for (int x = 0; x < maxActions; x++) //find the first action with the same button code
			{
				if (actions[x]->mouseButton == eventController::currentEvent.button.button) //if the codes match, call the keyDown function
				{
					actions[x]->keyDown();
					break;
				}
			}
		}

		if (eventController::currentEvent.type == SDL_MOUSEBUTTONUP) //when a mouse button is released
		{
			for (int x = 0; x < maxActions; x++) //find the first action with the same button code
			{
				if (actions[x]->mouseButton == eventController::currentEvent.button.button)//if the codes match, call the keyUp function
				{
					actions[x]->keyUp();
					break;
				}
			}
		}

		Uint32 buttonStates = SDL_GetMouseState(nullptr, nullptr); //get the state of the mouse

		for (int x = 0; x < maxActions; x++) //loop through every action
		{
			if (keyStates[actions[x]->mouseButton]) //if the button is pressed down
			{
				actions[x]->keyIsDown();
			}
		}
	}
}

actionController::~actionController()
{
	for (int x = 0; x < maxActions; x++) //delete every action object
	{
		delete actions[x];
	}
}
