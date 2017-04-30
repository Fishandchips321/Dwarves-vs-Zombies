#pragma once
#include <SDL.h>
class action
{
public:
	action();
	virtual void keyDown();
	virtual void keyUp();
	~action();
	SDL_Keycode key;
};

