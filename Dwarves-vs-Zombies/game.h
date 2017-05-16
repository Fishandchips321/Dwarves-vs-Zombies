#pragma once
#include <boost/thread.hpp>
#include <SDL2_framerate.h>
#include <iostream>
#include "netController.h"
#include "entityController.h"
#include "UIController.h"
#include "render.h"
#include "initializer.h"
#include "worldController.h"
#include "keybindController.h"
#include "AIController.h"
#include "actionController.h"
#include "tester.h"


class game
{
public:
	game();
	bool startGameLoop();
	bool init();
	~game();
private:

	enum class gameStates
	{
		splash,
		lobby,
		play,
		over,
		end,
		load
	};

	const int FPS = 60;
	const int screenTicksPerFrame = 1000 / FPS;
	gameStates myGameState;

	void update();
	void eventUpdate();
	void netUpdate();
	void controlNetUpdate();
	void draw();

	worldController world;

	FPSmanager* FPSman;

	tester test;
};

