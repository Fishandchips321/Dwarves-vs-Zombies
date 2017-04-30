#pragma once
#include <SDL.h>
#include "render.h"
#include "imageService.h"
#include "eventController.h"
class slider
{
public:
	slider(int x, int y, int length, bool vert = false);
	void init(int ID, int menuID, void(*func)(int));
	void update();
	void eventUpdate();
	void draw();
	~slider();

	enum state
	{
		default,//the normal state of the slider
		hover,//the mouse is over the slider (not the "rail")
		clicked,//the mouse is over the slider and has been clicked (mouse button down)
		moving,//the slider has been clicked and the mouse isn't over the slider
		disabled//the slider won't be effected by mouse events
	};

	state state = state::default;
	bool railMove;
private:
	SDL_Rect railRect;
	SDL_Rect sliderRect;
	SDL_Texture *textures[6];
	void(*onChange)(int);
	bool vert;
	int ID, menuID;
	int yPosLast;
	int xPosLast;

	const int width = 20;
	const int railClickedSpeed = 5;
};

