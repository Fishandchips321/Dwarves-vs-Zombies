#include "entityController.h"

std::vector<entity* > entityController::entities;

entityController::entityController()
{
}

void entityController::update()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->update();
	}
	collisionDetection();
}

void entityController::collisionDetection()
{
	/*
		todo:
		iterate through entities
		check collision between all
	*/
}

void entityController::eventUpdate()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->eventUpdate();
	}
}

void entityController::draw()
{
	//if the entity is on the screen draw it
	for (int i = 0; i < int(entities.size()); i++) //doesn't count the element at value "size"
	{
		if (entities[i]->entityRect.x + render::xOffset >= 0 && ((entities[i]->entityRect.x + render::xOffset) + entities[i]->entityRect.w) <= render::screenWidth)
		{
			if (entities[i]->entityRect.y + render::yOffset >= 0 && ((entities[i]->entityRect.y + render::yOffset) + entities[i]->entityRect.h) <= render::screenHeight)
			{
				entities[i]->draw();
			}
		}
	}
}

bool entityController::registerEntity(entity* newEnt)
{

	if (newEnt != nullptr)
	{
		entities.push_back(newEnt);

		return true;
	}

	return false;
}

void entityController::detectCollision(entity* entity1, entity* entity2)
{

	if (entity1->entityRect.x >= entity2->entityRect.x && entity1->entityRect.x <= entity2->entityRect.x + entity2->entityRect.w)
	{
		if (entity1->entityRect.y >= entity2->entityRect.y && entity1->entityRect.y <= entity2->entityRect.y + entity2->entityRect.h)
		{
			entity1->onCollide(entity2);
		}
	}

	if (entity2->entityRect.x >= entity1->entityRect.x && entity2->entityRect.x <= entity1->entityRect.x + entity1->entityRect.w)
	{
		if (entity2->entityRect.y >= entity1->entityRect.y && entity2->entityRect.y <= entity1->entityRect.y + entity1->entityRect.h)
		{
			entity2->onCollide(entity1);
		}
	}
}

entityController::~entityController()
{
	for (int x = 0; x > int(entities.size()); x++)
	{
		delete entities[x];
	}
}
