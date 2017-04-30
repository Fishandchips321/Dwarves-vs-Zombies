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



using namespace std;

class initializer
{
public:
	initializer();
	bool initAll();
	bool initRender();
	bool initSDL();
	bool initEventCont();
	bool initUI();
	~initializer();
private:
};

