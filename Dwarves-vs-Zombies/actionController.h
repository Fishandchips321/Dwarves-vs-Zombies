#pragma once
#include <SDL.h>
#include "action.h"
#include "eventController.h"
#include "UIController.h"

#define maxActions 9

class actionController
{
public:
	actionController();
	static bool registerAction(action *a, SDL_Keycode key, int action); //only called by the init class
	static bool rebindAction(int action, SDL_Keycode key); //called to rebind a key
	static void eventUpdate();
	~actionController();

	enum actions
	{
		escMenu,
		moveForward,
		moveBackward,
		moveLeft,
		moveRight,
		attack,
		use,
		walk,
		sprint
	};
private:
	static action* actions[maxActions];
};

