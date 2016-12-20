#pragma once
#include "imageService.h"
#include "render.h"
#include "resources.h"
class tester
{
public:
	tester();
	void init();
	void draw();
	~tester();
	SDL_Texture* testText;
	SDL_Rect rect;
};

