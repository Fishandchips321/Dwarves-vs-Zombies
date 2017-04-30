#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
class render
{
public:
	render();
	static bool init();
	static bool update();
	static bool drawScreen();
	static bool drawTexture(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* viewport = NULL);
	static bool drawSurface(SDL_Surface* surface, SDL_Rect* rect, SDL_Rect* viewport);
	static bool drawLight(int x, int y, int radius);
	static bool setLight(int lightLevel);
	static bool drawSquare(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	static int screenWidth; //640
	static int screenHeight; //480
	static int xOffset, yOffset;
	static std::string windowTitle;
	static SDL_Window* window;
	static SDL_Surface* screenSurface;
	static SDL_Renderer* renderer;

private:
	struct light
	{
		int x, y, radius;
	};

	static SDL_Texture* lightSurface; //holds the shadow (a black rectangle). change the alpha to make it darker or lighter
	static int lightAlpha;
	static std::vector<light> lights;
	~render();
};

