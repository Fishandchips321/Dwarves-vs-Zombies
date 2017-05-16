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
	virtual void init(int ID);
	virtual void update();
	virtual void eventUpdate();
	virtual void draw();
	virtual void loseFocus();
	~menuHandler();

	int ID;
};

