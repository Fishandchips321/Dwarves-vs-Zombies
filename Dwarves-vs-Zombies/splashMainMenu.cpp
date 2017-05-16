#include "splashMainMenu.h"
#include "UIController.h" //do not use UIController in any class functions (i.e. any function with "splashMainMenu" in front)

void showQuickplay()
{
	UIController::showMenu(UIController::quickPlayMenu);
}

void showServers()
{
	UIController::showMenu(UIController::serversMenu);
}

void showOptions()
{
	UIController::showMenu(UIController::optionsMenu);
}

void quitGame()
{
	SDL_Event *e = new SDL_Event;
	//SDL_memset(&e, 0, sizeof(e));
	e->type = eventController::quitGame;
	SDL_PushEvent(e);
}

splashMainMenu::splashMainMenu()
	:quickPlay(0, 0, 300, 50, "Quick Play"),
	servers(0, 100, 300, 50, "Servers"),
	options(0, 200, 300, 50, "Options"),
	quit(0, 300, 300, 50, "Quit")
{
	rect.x = rect.y = 0;
	rect.w = render::screenWidth;
	rect.h = render::screenHeight;

	background = imageService::loadTexture("assets/textures/tester.png");
}

void splashMainMenu::init(int ID)
{
	quickPlay.init(0, ID, showQuickplay);
	servers.init(1, ID, showServers);
	options.init(2, ID, showOptions);
	quit.init(3, ID, quitGame);

	menuHandler::init(ID);
}

void splashMainMenu::eventUpdate()
{
	quickPlay.eventUpdate();
	servers.eventUpdate();
	options.eventUpdate();
	quickPlay.eventUpdate();
}

void splashMainMenu::draw()
{
	//render::drawTexture(background, &rect);
	quickPlay.draw();
	servers.draw();
	options.draw();
	quickPlay.draw();
}

splashMainMenu::~splashMainMenu()
{
}