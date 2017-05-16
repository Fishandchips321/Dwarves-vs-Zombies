#include "tester.h"



tester::tester()
{
}

void tester::init()
{
	SDL_Texture* load = imageService::loadTexture("assets/textures/UI/button.png");
}

void tester::eventUpdate()
{
	if (eventController::currentEvent.type == SDL_KEYDOWN)
	{
		if (eventController::currentEvent.key.keysym.sym == SDLK_DOWN)
		{
			clipRect.y++;
		}

		if (eventController::currentEvent.key.keysym.sym == SDLK_UP)
		{
			clipRect.y--;
		}

		if (eventController::currentEvent.key.keysym.sym == SDLK_LEFT)
		{
			clipRect.x--;
		}

		if (eventController::currentEvent.key.keysym.sym == SDLK_RIGHT)
		{
			clipRect.x++;
		}
	}
}

void tester::draw()
{
	render::drawTexture(testTexture, &rect);
}

tester::~tester()
{
}
