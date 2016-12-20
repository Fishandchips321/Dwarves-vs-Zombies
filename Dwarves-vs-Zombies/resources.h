#pragma once
#include <SDL.h>
#include <vector>


class resources
{
public:
	resources();
	~resources();

	static SDL_Event* currentEvent;
};