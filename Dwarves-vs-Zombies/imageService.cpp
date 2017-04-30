#include "imageService.h"
#include <iostream>

const std::string imageService::fonts[] = { "assets/fonts/kenvector_future.ttf", "assets/fonts/kenvector_future_thin.ttf" };

imageService::imageService()
{
}

SDL_Texture* imageService::loadTexture(std::string path, bool reload)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "[ERROR]: Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(render::renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "[ERROR]: Unable to create texture from " << path << "!SDL Error : " << SDL_GetError() << std::endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	std::cout << "[INFO]: The image \"" << path << "\" was loaded and made into a texture" << std::endl;

	return newTexture;
}

SDL_Texture* imageService::loadText(std::string text, SDL_Color colour, int font, int size)
{
	TTF_Font* Tfont = loadFont(fonts[font], size);

	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;
	textSurface = TTF_RenderText_Solid(Tfont, text.c_str(), colour);
	if (textSurface == NULL)
	{
		std::cout << "[ERROR]: couldn't make text surface\"" << text << "\" with font " << font << ". SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	textTexture = SDL_CreateTextureFromSurface(render::renderer, textSurface);

	if (textTexture == nullptr)
	{
		std::cout << "[ERROR]: couldn't get texture from text surface. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return textTexture;
}

TTF_Font* imageService::loadFont(std::string path, int size)
{
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);

	if (font != nullptr)
		return font;

	return nullptr;
}

imageService::~imageService()
{
}
