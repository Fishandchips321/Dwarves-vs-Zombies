#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class windowRenderer
{
public:
	windowRenderer();
	bool init(std::string name, int w, int h);
	bool update();
	bool drawScreen();
	bool drawTexture(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* viewport = nullptr);
	bool drawSquare(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	int screenWidth;
	int screenHeight;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	~windowRenderer();
};

