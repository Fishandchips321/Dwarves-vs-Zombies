#pragma once
#include <SDL.h>
#include <vector>
#include <utility>
#include "keyBindAction.h"
#include "eventController.h"
class keybindController
{
public:
	keybindController();
	static void eventUpdate();
	static bool bindKey(int keycode, keyBindAction action);
	static bool unbindKey(int keycode);
	static bool bindMouse(int keycode, keyBindAction action);
	static bool unbindMouse(int keycode);
	~keybindController();

private:
	static std::vector<std::pair<int, keyBindAction>> keyBindings;
	static std::vector<std::pair<int, keyBindAction>> mouseBindings;
};

