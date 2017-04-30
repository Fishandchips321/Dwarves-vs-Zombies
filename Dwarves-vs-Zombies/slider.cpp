#include "slider.h"



slider::slider(int x, int y, int length, bool vert)
{
}

void slider::init(int ID, int menuID, void(*func)(int))
{
	slider::ID = ID;
	slider::menuID = menuID;

	onChange = func;
}

void slider::update()
{
}

void slider::eventUpdate()
{
	if (state != state::disabled) //if the button isn't disabled
	{
		if (eventController::currentEvent.type == SDL_MOUSEBUTTONDOWN && eventController::currentEvent.button.button == SDL_BUTTON_LEFT)//if the left mouse button was pressed down
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			SDL_Rect mouseRect = { x, y, 0, 0 };

			if (SDL_HasIntersection(&sliderRect, &mouseRect))//if the mouse is over the slider
			{
				state = state::clicked;
				if (vert)
					yPosLast = sliderRect.y;
				else
					xPosLast = sliderRect.x;
			}
			else if (SDL_HasIntersection(&railRect, &mouseRect))//if the mouse clicked on the slider's rail
			{
				railMove = true;
				if (vert)
					yPosLast = sliderRect.y;
				else
					xPosLast = sliderRect.x;
			}
		}

		if (eventController::currentEvent.type == SDL_MOUSEBUTTONUP && eventController::currentEvent.button.button == SDL_BUTTON_LEFT)//if the left mouse button is raised
		{
			if (state == state::clicked)
				state = state::hover;

			if (state == state::moving)
				state = state::default;

			if (railMove)
				railMove = false;
		}

		if (eventController::currentEvent.type == SDL_MOUSEMOTION)//if the mouse has moved, check if it's over the button or not
		{
			if (state == state::default)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				SDL_Rect mouseRect = { x, y, 0, 0 };

				if (SDL_HasIntersection(&sliderRect, &mouseRect))//if the mouse is over the button
				{
					state = state::hover;


				}

			}

			if (state == state::clicked || state == state::moving)//if the slider is being used
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				SDL_Rect mouseRect = { x, y, 0, 0 };

				if (SDL_HasIntersection(&sliderRect, &mouseRect))//if the mouse is over the button
					state = state::clicked;
				else
					state = state::moving;

				if (vert)//if the slider is vertical, move the slider vertically
				{
					sliderRect.y = mouseRect.y;

					if (sliderRect.y < railRect.y)//stop the slider from going too far up
						sliderRect.y = railRect.y;

					if (sliderRect.y + sliderRect.h > railRect.y + railRect.h)//stop the slider from going too far down
						sliderRect.y = railRect.y + sliderRect.h;

					onChange(y - yPosLast);//report the change
				}
				else//if the slider is horizontal, move the slider horizontally
				{
					sliderRect.x = mouseRect.x;

					if (sliderRect.x < railRect.x)//stop the slider from going too far left
						sliderRect.x = railRect.x;

					if (sliderRect.x + sliderRect.w > railRect.x + railRect.w)//stop the slider going too far right
						sliderRect.x = railRect.x + sliderRect.w;

					onChange(x - xPosLast);//report the change
				}
			}
		}

		if (railMove)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			SDL_Rect mouseRect = { x, y, 0, 0 };

			if (vert)//if the slider is vertical
			{
				if (sliderRect.y > mouseRect.y)//if the slider is below the mouse
				{
					sliderRect.y += railClickedSpeed;
					onChange(sliderRect.y - yPosLast);
				}
				else if (sliderRect.y < mouseRect.y)//if the slider is above the mouse
				{
					sliderRect.y -= railClickedSpeed;
					onChange(sliderRect.y - yPosLast);
				}
			}
			else
			{
				if (sliderRect.x > mouseRect.x)//if the slider is below the mouse
				{
					sliderRect.x += railClickedSpeed;
					onChange(sliderRect.x - xPosLast);
				}
				else if (sliderRect.x < mouseRect.x)//if the slider is above the mouse
				{
					sliderRect.x -= railClickedSpeed;
					onChange(sliderRect.x - xPosLast);
				}
			}

			if (SDL_HasIntersection(&sliderRect, &mouseRect) && railMove)//if the rail has been clicked and the slider moves under the mouse, stop rail moving
			{
				railMove = false;
			}
		}
	}
}

void slider::draw()
{
	render::drawTexture(textures[state], &sliderRect);//draw the slider

	render::drawTexture(textures[5], &railRect);//draw the rail
}


slider::~slider()
{
}
