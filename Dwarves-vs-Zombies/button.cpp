#include "button.h"



button::button(int x, int y, int w, int h, std::string text)
{

}

void button::init(int ID, int menuID, void(*func)())
{
	button::ID = ID;
	button::menuID = menuID;

	onClick = func;
}

void button::eventUpdate()
{
	if (state != state::disabled) //if the button isn't disabled
	{
		if (eventController::currentEvent.type == SDL_MOUSEBUTTONDOWN && eventController::currentEvent.button.button == SDL_BUTTON_LEFT)//if the left mouse button was pressed down
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			SDL_Rect mouseRect = { x, y, 0, 0 };

			if (SDL_HasIntersection(&buttonRect, &mouseRect))//if the mouse is over the button
			{
				state = state::clicked;
			}
		}

		if (eventController::currentEvent.type == SDL_MOUSEBUTTONUP && eventController::currentEvent.button.button == SDL_BUTTON_LEFT)//if the left mouse button is raised
		{
			if (state == state::clicked)
			{
				state = state::hover;
				onClick();//report the click event
			}

			if (state == state::down)
			{
				state = state::up;
				onClick();//report the click event
			}
		}

		if (eventController::currentEvent.type == SDL_MOUSEMOTION)//if the mouse has moved, check if it's over the button or not
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			SDL_Rect mouseRect = { x, y, 0, 0 };

			if (SDL_HasIntersection(&buttonRect, &mouseRect))//if the mouse is over the button
			{
				if (state == state::up)
					state = state::hover;
			}
			else//if the mouse isn't over the button
			{
				if (state == state::clicked)
					state = state::down;

				if (state == state::hover)
					state = state::up;
			}
		}
	}
}

void button::update()
{

}

void button::draw()
{

}

button::~button()
{
}
