#include "windowRenderer.h"


windowRenderer::windowRenderer()
{
}

bool windowRenderer::init(std::string name, int w, int h)
{
	screenWidth = w;
	screenHeight = h;

	//create the window
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL) // if the window wasn't created
	{
		std::cout << "[ERROR]: An error occured in render. SDL error " << SDL_GetError() << std::endl;
		return false;
	}

	//initialize the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xff);
	}
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0)
	{
		std::cout << "[ERROR]: couln't set blendmode" << std::endl;
		return false;
	}

	std::cout << "[INFO]: The renderer was successfully initialised" << std::endl;
	return true;

}

bool windowRenderer::update()
{
	return true;
}

bool windowRenderer::drawScreen()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xff);
	SDL_RenderPresent(renderer);

	SDL_RenderClear(renderer);
	return true;
}

bool windowRenderer::drawTexture(SDL_Texture * texture, SDL_Rect * rect, SDL_Rect * viewport)
{
	if (texture == nullptr)
		return false;
	if (SDL_RenderCopy(renderer, texture, viewport, rect) != 0)
	{
		std::cout << "[ERROR]: Problem rendering texture " << texture << ". SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool windowRenderer::drawSquare(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	if (SDL_RenderFillRect(renderer, &rect) != 0)
	{
		std::cout << "[ERROR]: Problem filling rectangle " << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << ". SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

windowRenderer::~windowRenderer()
{
	// destroy the window and NULL the pointer
	SDL_DestroyWindow(window);
	window = NULL;
}
