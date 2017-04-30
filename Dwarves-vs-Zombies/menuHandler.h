#pragma once
#include <utility>
#include <SDL.h>
#include "button.h"
#include "slider.h"
#include "render.h"
class menuHandler
{
public:
	menuHandler();
	void init(int ID);
	void update();
	void eventUpdate();
	void draw();
	~menuHandler();

	bool visible;
	int ID;
};

