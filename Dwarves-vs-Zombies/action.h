#pragma once
#include <SDL.h>
class action
{
public:
	action();
	virtual void keyDown();
	virtual void keyUp();
	virtual void keyIsDown();
	~action();
	SDL_Keycode key;
	Uint8 mouseButton;
	
};

