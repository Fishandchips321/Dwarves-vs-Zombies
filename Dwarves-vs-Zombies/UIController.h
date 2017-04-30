#pragma once
#include <SDL.h>
#include "menuHandler.h"
#include <vector>

#define maxMenus 5

class UIController
{
public:
	UIController();
	static void update();
	static void eventUpdate();
	static void draw();
	static void registerMenu(menuHandler menu);
	static int getFocus();
	static bool showMenu(int menu);
	~UIController();

	enum menuIDs
	{
		gameScreen,
		splashMenu,
		quickPlayMenu,
		serversMenu,
		optionsMenu,
		escMenu,
		deathMenu,
		lobby
	};

private:

	static std::vector<menuHandler> menus;

	

	static int focus;
};

