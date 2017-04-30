#pragma once
#include "menuHandler.h"
#include "eventController.h"
class splashMainMenu : public menuHandler
{
public:
	splashMainMenu();
	void init(int ID);
	void eventUpdate();
	void draw();
	~splashMainMenu();

private:
	button quickPlay;
	button servers;
	button options;
	button quit;

	const int buttonWidth = 100;
	const int buttonHeight = 20;
	const int buttonSpacing = 10;

	void(*quickPlayF)();
	void(*serversF)();
	void(*optionsF)();
	void(*quitF)();
};

