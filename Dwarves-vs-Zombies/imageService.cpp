#include "imageService.h"
#include <iostream>

const std::string imageService::fonts[] = { "assets/fonts/kenvector_future.ttf", "assets/fonts/kenvector_future_thin.ttf" };

imageService::imageService()
{
}

SDL_Texture* imageService::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "[ERROR]: Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(render::renderer, loadedSurface); //create a texture with the image on the surface
		if (newTexture == nullptr)
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
	TTF_Font* Tfont = loadFont(fonts[font], size); //loads the chosen font at the specified size

	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr;
	textSurface = TTF_RenderText_Solid(Tfont, text.c_str(), colour); //draw the text with the font onto the surface
	if (textSurface == nullptr) //if nothing was returned print an error message and return false
	{
		std::cout << "[ERROR]: couldn't make text surface\"" << text << "\" with font " << font << ". SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	textTexture = SDL_CreateTextureFromSurface(render::renderer, textSurface); //transfer the image from the surface to the texture
	SDL_FreeSurface(textSurface); //clears the surface
	if (textTexture == nullptr) //if a texture wasn't returned, print an error message and return false
	{
		std::cout << "[ERROR]: couldn't get texture from text surface. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return textTexture; //return the end result
}

TTF_Font* imageService::loadFont(std::string path, int size)
{
	TTF_Font* font = TTF_OpenFont(path.c_str(), size); //loads the font pointed to by path and sets it to the specified size

	if (font != nullptr) //if the font isn't empty return it
		return font;

	return nullptr; //return nothing
}

SDL_Surface * imageService::loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); 
	SDL_Surface* optimisedSurface = nullptr;
	//if the image couldn't be loaded
	if (loadedSurface == nullptr)
	{
		std::cout << "[ERROR]: Could not load image \"" << path << "\". SDL Error " << SDL_GetError() << std::endl;
	}
	else
	{
		optimisedSurface = SDL_ConvertSurface(loadedSurface, render::screenSurface->format, 0);
		//if the image could not be optimised
		if (optimisedSurface == nullptr)
		{
			std::cout << "[ERROR]: Could not load image \"" << path << "\". SDL Error " << SDL_GetError() << std::endl;
		}
	}

	SDL_FreeSurface(loadedSurface); //clear the data from the surface (deletes the pointer)

	return optimisedSurface;
}

imageService::~imageService()
{
}
