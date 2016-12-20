#pragma once
#include "entity.h"
#include "resources.h"
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
	static void collisionDetection();
	static void detectCollision(entity* entity1, entity* entity2);

	static std::vector<entity* > entities;
};

