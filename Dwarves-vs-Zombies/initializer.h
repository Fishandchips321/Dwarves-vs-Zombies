#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include "counter.h"
#include "render.h"
#include "eventController.h"
#include "UIController.h"
#include "menus.h"
#include "actionController.h"
#include "allActions.h"



using namespace std;

class initializer
{
public:
	initializer();
	bool initAll();
	bool initSDL();
	bool initUI();
	bool initActions();
	~initializer();
private:
};

