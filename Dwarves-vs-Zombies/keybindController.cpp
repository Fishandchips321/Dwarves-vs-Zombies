#include "keybindController.h"

std::vector<std::pair<int, keyBindAction>> keybindController::keyBindings;
std::vector<std::pair<int, keyBindAction>> keybindController::mouseBindings;

keybindController::keybindController()
{
}

void keybindController::eventUpdate()
{
	//if the event is a key down event
	if (eventController::currentEvent.type == SDL_KEYDOWN)
	{
		for (size_t x = 0; x < keyBindings.size(); x++) //find a key binding with the correct key code and 
		{
			if (keyBindings[x].first == eventController::currentEvent.key.keysym.sym)
			{
				keyBindings[x].second.act();
			}
		}
	}
	else if (eventController::currentEvent.type == SDL_MOUSEBUTTONDOWN) //if the event is a mouse button down event
	{
		for (size_t x = 0; x < mouseBindings.size(); x++)
		{
			if (mouseBindings[x].first == eventController::currentEvent.button.button)
			{
				mouseBindings[x].second.act();
			}
		}
	}
}

bool keybindController::bindKey(int keycode, keyBindAction action)
{
	unbindKey(keycode);

	std::pair<int, keyBindAction> keyBind;
	keyBind.first = keycode;
	keyBind.second = action;

	keyBindings.push_back(keyBind);
	return true;
}

bool keybindController::unbindKey(int keycode)
{
	for (size_t x = 0; x < keyBindings.size(); x++)
	{
		if (keyBindings[x].first == keycode)
		{
			keyBindings.erase(keyBindings.begin() + x);
			return true;
		}
	}
	return false;
}

bool keybindController::bindMouse(int keycode, keyBindAction action)
{
	unbindMouse(keycode);

	std::pair<int, keyBindAction> keyBind;
	keyBind.first = keycode;
	keyBind.second = action;

	mouseBindings.push_back(keyBind);
	return true;
}

bool keybindController::unbindMouse(int keycode)
{
	for (size_t x = 0; x < mouseBindings.size(); x++)
	{
		if (mouseBindings[x].first == keycode)
		{
			mouseBindings.erase(mouseBindings.begin() + x);
			return true;
		}
	}
	return false;
}

keybindController::~keybindController()
{
}
