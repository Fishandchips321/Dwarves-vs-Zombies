#pragma once
#include "resources.h"
class render
{
public:
	render();
	static bool init();
	static bool update();
	static bool drawScreen();
	static bool drawTexture(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* viewport = NULL);
	static bool drawSquare(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	static int screenWidth; //640
	static int screenHeight; //480
	static int xOffset, yOffset;
	static std::string windowTitle;
	static SDL_Window* window;
	static SDL_Surface* screenSurface;
	static SDL_Renderer* renderer;
	~render();
};

