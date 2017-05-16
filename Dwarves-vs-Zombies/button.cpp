#include "button.h"



button::button(int x, int y, int w, int h, std::string text)
{
	buttonRect.x = x;
	buttonRect.y = y;
	buttonRect.w = w;
	buttonRect.h = h;

	clipRect.x = 0;
	clipRect.y = 0;
	clipRect.w = 120;
	clipRect.h = 28;

	SDL_Colour colour;
	colour.r = 0xff;
	colour.g = 0xff;
	colour.b = 0xff;
	colour.a = 0xff;

	button::text = imageService::loadText(text, colour, imageService::UIfont);

	TButton = imageService::loadTexture("assets/textures/UI/button.png");
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

			SDL_Rect mouseRect = { x, y, 1, 1};

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

			SDL_Rect mouseRect = { x, y, 1, 1};

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

		switch (state)
		{
		case up:
			clipRect.y = 0;
			break;
		case hover:
			clipRect.y = 28;
			break;
		case down:
			clipRect.y = 56;
			break;
		case clicked:
			clipRect.y = 56;
			break;
		}
	}
}

void button::update()
{

}

void button::draw()
{
	render::drawTexture(TButton, &buttonRect, &clipRect);
	render::drawTexture(text, &textRect);
}

button::~button()
{
	for (int x = 0; x < 5; x++)
	{
		SDL_DestroyTexture(TButton);
	}

	SDL_DestroyTexture(text);
	onClick = nullptr;
}