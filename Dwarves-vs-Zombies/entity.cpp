#include "entity.h"


entity::entity()
{
	entityTexture = imageService::loadTexture("assets/Textures/missing texture.png");
	int w, h;
	SDL_QueryTexture(entityTexture, NULL, NULL, &w, &h);
	entityRect = { 0, 0, w, h };
	flying = false;
}

void entity::update()
{
}

void entity::eventUpdate()
{
}

void entity::draw()
{
	SDL_Rect drawRect;
	drawRect.x = entityRect.x + render::xOffset;
	drawRect.x = entityRect.x + render::yOffset;
	drawRect.w = entityRect.w;
	drawRect.h = entityRect.h;

	render::drawTexture(entityTexture, &drawRect);
}

void entity::onCollide(entity* collider)
{
}

bool entity::damage(int amount, entity* damager)
{
	return false;
}

bool entity::push(int xVel, int yVel)
{
	return false;
}

void entity::unload()
{

}

entity::~entity()
{
}
