#pragma once
#include <SDL.h>
#include <iostream>
class eventController
{
public:
	eventController();
	static bool init();
	~eventController();

	enum events
	{
		disconnectNet = 32768
		
	};
};

