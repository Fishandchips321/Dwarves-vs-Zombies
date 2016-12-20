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
	//init the resource locator
	if (initRender())
	{
		cout << "[INFO]: Resource Locator initialized successfully" << endl;
	}
	else
	{
		cout << "[ERROR]: Resource Locator wasn't initialized correctly" << endl;
		success = false;
	}
	//initialise the event controller
	if (initEventCont())
	{
		cout << "[INFO]: Event Controller was initialized correctly" << endl;
	}
	else
	{
		cout << "[ERROR]: Event Controller wasn't initialized correctly" << endl;
		success = false;
	}
	return success;
}

bool initializer::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "[ERROR]: SDL failed to init. SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}
	else
	{
		cout << "[INFO]: SDL initalised." << endl;
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

bool initializer::initEventCont()
{
	return eventController::init();
}

bool initializer::initRender()
{
	return render::init();
}

initializer::~initializer()
{
}
