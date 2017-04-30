#pragma once
#include <SDL.h>
#include <string>
#include "render.h"
#include "imageService.h"
class button
{
public:
	button(int x, int y, int w, int h, std::string text);
	void init(int ID, int menuID, void(*func)());
	void update();
	void eventUpdate();
	void draw();
	~button();

	enum state
	{
		up, //the button's normal state
		hover, //the mouse is over the button
		clicked, //the mouse is over the button and the button is down
		down, //the button is down but the mouse isn't over the button
		disabled //the button won't change or do anything
	};

	state state = state::up;

	SDL_Rect buttonRect;
private:
	SDL_Rect textRect;
	SDL_Texture *textures[5];
	SDL_Texture *text;
	int ID, menuID;
	void(*onClick)();
};

