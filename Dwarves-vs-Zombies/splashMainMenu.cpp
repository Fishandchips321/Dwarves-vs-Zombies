#include "splashMainMenu.h"

void showQuickplay()
{
	SDL_Event* e;
	SDL_memset(&e, 0, sizeof(e));
	e->type = eventController::UIEvent;
	e->user.code = eventController::showQuickplayMenu;
	SDL_PushEvent(e);
}

void showServers()
{
	SDL_Event* e;
	SDL_memset(&e, 0, sizeof(e));
	e->type = eventController::UIEvent;
	e->user.code = eventController::showServerMenu;
	SDL_PushEvent(e);
}

void showOptions()
{
	SDL_Event* e;
	SDL_memset(&e, 0, sizeof(e));
	e->type = eventController::UIEvent;
	e->user.code = eventController::showOptionsMenu;
	SDL_PushEvent(e);
}

void quitGame()
{
	SDL_Event *e;
	SDL_memset(&e, 0, sizeof(e));
	e->type = eventController::quitGame;
	SDL_PushEvent(e);
}

splashMainMenu::splashMainMenu()
	:quickPlay((render::screenWidth / 2) - (buttonWidth / 2), 50, buttonWidth, buttonHeight, "Quick Play"),
	servers((render::screenWidth / 2) - (buttonWidth / 2), quickPlay.buttonRect.y + buttonSpacing + buttonHeight, buttonWidth, buttonHeight, "Servers"),
	options((render::screenWidth / 2) - (buttonWidth / 2), servers.buttonRect.y + buttonSpacing + buttonHeight, buttonWidth, buttonHeight, "Options"),
	quit((render::screenWidth / 2) - (buttonWidth / 2), options.buttonRect.y + buttonSpacing + buttonHeight, buttonWidth, buttonHeight, "Quit")
{
	quickPlayF = showQuickplay;
	serversF = showServers;
	optionsF = showOptions;
	quitF = quitGame;
}

void splashMainMenu::init(int ID)
{
	quickPlay.init(0, ID, quickPlayF);
	servers.init(1, ID, serversF);
	options.init(2, ID, optionsF);
	quit.init(3, ID, quitF);

	menuHandler::init(ID);
}

void splashMainMenu::eventUpdate()
{
	if (visible)
	{
		quickPlay.eventUpdate();
		servers.eventUpdate();
		options.eventUpdate();
		quickPlay.eventUpdate();
	}
}

void splashMainMenu::draw()
{
	if (visible)
	{
		quickPlay.draw();
		servers.draw();
		options.draw();
		quickPlay.draw();
	}
}

splashMainMenu::~splashMainMenu()
{
}