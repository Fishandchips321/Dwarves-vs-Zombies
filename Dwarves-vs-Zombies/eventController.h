#pragma once
#include <SDL.h>
#include <iostream>

#define eventNO 10

class eventController
{
public:
	eventController();
	static bool init();
	static bool nextEvent();
	static void sendEvent(int event, void* data1 = nullptr, void* data2 = nullptr);
	~eventController();

	static SDL_Event currentEvent;

	enum events
	{
		disconnectNet = 32768,
		UIEvent,
		quitGame,
		mapLoaded,
		mapLoadError,
		quickExit,
		loginError,
		authError,
		spawnPlayer,
		playerEvent
	};

	enum UIEvents
	{
		showMenu,
		lobbyPlayerUpdate
	};

	enum playerEvents
	{
		moveForward,
		moveBack,
		moveLeft,
		moveRight,
		attack,
		use,
		walk,
		sprint,
		run
	};

	struct playerSpawn
	{
		int playerID, x, y, playerClass;
	};
};

