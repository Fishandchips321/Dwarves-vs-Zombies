#pragma once
#include <SDL.h>
#include "render.h"
class UIController
{
public:
	UIController();
	void update();
	void eventUpdate();
	void draw();
	~UIController();
};

