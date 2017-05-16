#include "initializer.h"


initializer::initializer()
{
}

bool initializer::initAll()
{
	bool success = true;
	//init SDL
	if (initSDL())
	{
		cout << "[INFO]: SDL was initialized successfully" << endl;
	}
	else
	{
		cout << "[ERROR]: SDL wasn't initialised" << endl;
		success = false;
	}
	//init the renderer
	if (render::init())
	{
		cout << "[INFO]: Resource Locator initialized successfully" << endl;
	}
	else
	{
		cout << "[ERROR]: Resource Locator wasn't initialized correctly" << endl;
		success = false;
	}
	//initialise the event controller
	if (eventController::init())
	{
		cout << "[INFO]: Event Controller was initialized correctly" << endl;
	}
	else
	{
		cout << "[ERROR]: Event Controller wasn't initialized correctly" << endl;
		success = false;
	}
	//initailise all UI stuff
	if (initUI())
	{
		cout << "[INFO]: UI was initialised successfully" << endl;
	}
	else
	{
		cout << "[ERROR]: UI wasn't initialised correctly" << endl;
		success = false;
	}
	return success;
}

bool initializer::initSDL()
{
	//initialises the SDL SDK
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "[ERROR]: SDL failed to init. SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}
	else
	{
		cout << "[INFO]: SDL initalised." << endl;
		//initialises SDL_IMG
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			cout << "[ERROR]: IMG didn't initialise properly. SDL Error " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			cout << "[INFO]: IMG initialised." << endl;
			//Initialize SDL_ttf
			if (TTF_Init() == -1)
			{
				cout << "[ERROR]: SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
				return false;
			}
			else
			{
				return true;
			}
		}

	}
}

bool initializer::initUI()
{
	//create and register all of the menu objects
	splashMainMenu *splash = new splashMainMenu;
	UIController::registerMenu(splash);
	return UIController::showMenu(UIController::splashMenu);
}

bool initializer::initActions()
{
	//add all of the actions to the action controller. if an add action fails, return false
	bool success = true;
	escMenu* esc = new escMenu;
	if (!actionController::registerAction(esc, SDLK_ESCAPE, actionController::escMenu))
		success = false;
	moveForward* forw = new moveForward;
	if (!actionController::registerAction(forw, SDLK_w, actionController::moveForward))
		success = false;
	moveBackward* bac = new moveBackward;
	if (!actionController::registerAction(bac, SDLK_s, actionController::moveBackward))
		success = false;
	moveLeft* lef = new moveLeft;
	if (!actionController::registerAction(lef, SDLK_a, actionController::moveLeft))
		success = false;
	moveRight *rig = new moveRight;
	if (!actionController::registerAction(rig, SDLK_d, actionController::moveRight))
		success = false;
	action *att = new action; // update me
	if (!actionController::registerAction(att, SDL_BUTTON_LEFT, actionController::attack))
		success = false;
	action *use = new action; //update me
	if (!actionController::registerAction(use, SDL_BUTTON_RIGHT, actionController::use))
		success = false;
	walk *wal = new walk;
	if (!actionController::registerAction(rig, SDLK_LCTRL, actionController::walk))
		success = false;
	sprint* spr = new sprint;
	if (!actionController::registerAction(rig, SDLK_LSHIFT, actionController::sprint))
		success = false;

	return success;
}

initializer::~initializer()
{
}
