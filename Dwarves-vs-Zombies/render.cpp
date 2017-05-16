#include "render.h"
#include <SDL2_gfxPrimitives.h>
#include "imageService.h"


int render::xOffset, render::yOffset;
SDL_Window* render::window = nullptr;
SDL_Surface* render::screenSurface = nullptr;
SDL_Renderer* render::renderer = nullptr;
int render::screenWidth = 640;
int render::screenHeight = 480;
std::string render::windowTitle = "";
SDL_Texture* render::lightSurface;
int render::lightAlpha = 0;
std::vector<render::light> render::lights;

render::render()
{
}

bool render::init()
{
	xOffset = 0;
	yOffset = 0;
	//create the window
	window = SDL_CreateWindow("Dwarves vs Zombies - InDev", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL) // if the window wasn't created
	{
		std::cout << "[ERROR]: An error occured in render. SDL error " << SDL_GetError() << std::endl;
		return false;
	}

	//initialize the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "[ERROR]: Renderer couldn't be created. SDL Error " << SDL_GetError() << std::endl;
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
	screenSurface = SDL_GetWindowSurface(window);
	SDL_SetWindowIcon(window, imageService::loadSurface("assets/textures/icon.png"));

	std::cout << "[INFO]: The renderer was successfully initialised" << std::endl;
	return true;

}

bool render::drawScreen()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xff);

	SDL_Rect screen;
	screen.x = screen.y = 0; screen.h = screenHeight; screen.w = screenWidth;
	drawSquare(screen, 0, 0, 0, lightAlpha);

	for (size_t x = 0; x < lights.size(); x++)
	{
		filledCircleRGBA(renderer, lights[x].x, lights[x].y, lights[x].radius, 255, 255, 255, 50);
	}

	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	return true;
}

bool render::update()
{
	return true;
}

bool render::drawLight(int x, int y, int radius)
{
	light l;
	l.x = x;
	l.y = y;
	l.radius = radius;

	lights.push_back(l);

	return true;
}

bool render::setLight(int lightLevel)
{
	return false;
}

bool render::drawSquare(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	if (SDL_RenderFillRect(renderer, &rect) != 0)
	{
		std::cout << "[ERROR]: Problem filling rectangle " << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << ". SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool render::drawTexture(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* viewport)
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

bool render::drawSurface(SDL_Surface* surface, SDL_Rect* rect, SDL_Rect* viewport)
{
	return false;
}

render::~render()
{
	// destroy the window and NULL the pointer
	SDL_DestroyWindow(window);
	window = NULL;
}
