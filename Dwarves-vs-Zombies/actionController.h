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
	static bool registerAction(action *a, SDL_Keycode key, int action);
	static bool rebindAction(int action, SDL_Keycode key);
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

