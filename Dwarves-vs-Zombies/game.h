#pragma once
#include <boost/thread.hpp>
#include "resources.h"
#include "counter.h"
#include "render.h"
#include "initializer.h"
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
		play,
		paused,
		over,
		end
	};

	const int FPS = 60;
	const int screenTicksPerFrame = 1000 / FPS;
	gameStates myGameState;

	void update();
	void eventUpdate();
	void draw();

	tester test;
};

