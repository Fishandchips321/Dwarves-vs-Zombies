#include "game.h"


game::game()
{
}

bool game::init()
{
	initializer initOb;
	if (!initOb.initAll())
	{
		return false;
	}
	myGameState = gameStates::splash;
	FPSman = new FPSmanager;
	SDL_initFramerate(FPSman);
	SDL_setFramerate(FPSman, 60);

	test.init();
	return true;
}

bool game::startGameLoop()
{
	bool quit = false;
	std::cout << "[INFO]: Entering the game loop" << std::endl;

	while (!quit && myGameState != gameStates::end)
	{
		while (eventController::nextEvent()) //poll events
		{
			if (eventController::currentEvent.type == SDL_QUIT) //if the window X button was pressed
			{
				quit = true;
			}

			if (eventController::currentEvent.type == SDL_KEYDOWN && eventController::currentEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				myGameState = gameStates::end;
			}

			eventUpdate();
		}

		if (netController::connected)
		{
			while (netController::nextMessage())
			{
				netUpdate();
			}

			while (netController::nextControlMessage())
			{
				netController::update();

				if (netController::currentControlMessage.NCM == netController::USER_ID)
				{
					netController::netID = std::stoi(netController::currentControlMessage.paramaters);
				}

				if (netController::currentControlMessage.NCM == netController::LOAD_MAP && myGameState == gameStates::lobby)
				{
					myGameState = gameStates::load;
				}

				if (netController::currentControlMessage.NCM == netController::KEEPALIVE_PING)
				{
					netController::send(std::to_string(netController::KEEPALIVE_PONG));
				}

				controlNetUpdate();
			}
		}

		//update then draw the game
		update();
		draw();

		SDL_framerateDelay(FPSman);
	}

	return true;
}

void game::eventUpdate()
{
	switch (myGameState)
	{
	case gameStates::play:
		entityController::eventUpdate();
		AIController::eventUpdate();
		break;
	case gameStates::lobby:
		break;
	case gameStates::splash:
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	}
	UIController::eventUpdate();
	keybindController::eventUpdate();
}

void game::netUpdate()
{
	switch (myGameState)
	{
	case gameStates::play:
		AIController::netUpdate();
		break;
	case gameStates::lobby:
		break;
	case gameStates::splash:
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	case gameStates::load:
		break;
	}
}

void game::controlNetUpdate()
{
	switch (myGameState)
	{
	case gameStates::play:
		break;
	case gameStates::lobby:
		break;
	case gameStates::splash:
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	case gameStates::load:
		break;
	}
	world.controlNetUpdate();
}

void game::update()
{
	switch (myGameState)
	{
	case gameStates::play:
		entityController::update();
		AIController::update();
		world.update();
		break;
	case gameStates::lobby:
		break;
	case gameStates::splash:
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	}
	UIController::update();
	render::update();
}

void game::draw()
{
	switch (myGameState)
	{
	case gameStates::play:
		entityController::draw();
		world.draw();
		break;
	case gameStates::lobby:
		break;
	case gameStates::splash:
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	}

	test.draw();
	UIController::draw();
	render::drawScreen(); //no touchey
}

game::~game()
{
}
