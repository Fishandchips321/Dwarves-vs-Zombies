#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "render.h"
#include "eventController.h"
class imageService
{
public:
	imageService();
	static SDL_Texture* loadText(std::string text, SDL_Color colour, int font, int size = 1);
	static SDL_Texture* loadTexture(std::string path);
	static TTF_Font* loadFont(std::string path, int size);
	static SDL_Surface* loadSurface(std::string path);
	~imageService();

	enum commonFonts
	{
		UIfont,
		UIfont_thin
	};
	static const std::string fonts[];
};

