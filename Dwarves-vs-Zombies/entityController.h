#pragma once
#include "entity.h"
#include "render.h"

class entityController
{
public:
	entityController();
	static void update();
	static void eventUpdate();
	static void draw();
	static bool registerEntity(entity* newEnt);
	~entityController();
private:

	static std::vector<entity* > entities;
};

