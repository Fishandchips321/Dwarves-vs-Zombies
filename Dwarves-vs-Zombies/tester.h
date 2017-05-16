#pragma once
#include "imageService.h"
#include "render.h"
#include "eventController.h"
class tester
{
public:
	tester();
	void init();
	void eventUpdate();
	void draw();
	~tester();
	SDL_Rect clipRect;
	SDL_Texture* testTexture;
	SDL_Rect rect;
};

