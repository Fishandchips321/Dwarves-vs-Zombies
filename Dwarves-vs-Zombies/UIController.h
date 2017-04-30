#pragma once
#include <SDL.h>
#include "menuHandler.h"
#include <vector>
class UIController
{
public:
	UIController();
	static void update();
	static void eventUpdate();
	static void draw();
	static void registerMenu(menuHandler menu);
	~UIController();
private:
	static void hideAll();

	static std::vector<menuHandler> menus;

	enum menuIDs
	{
		splashMenu,
		quickPlayMenu,
		serversMenu,
		optionsMenu
	};
};

