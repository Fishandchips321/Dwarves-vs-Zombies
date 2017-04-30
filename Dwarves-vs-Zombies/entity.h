#pragma once
#include "render.h"
#include "imageService.h"

class entity
{
	friend class AIPackage;
public:
	entity();
	virtual void update();
	virtual void eventUpdate();
	virtual void draw();
	virtual void onCollide(entity* collider);
	virtual bool damage(int amount, entity* damager);
	virtual bool push(int xVel, int yVel);
	virtual void unload();

	SDL_Rect entityRect;
	SDL_Texture* entityTexture;
	int xVel, yVel;
	int speed;
	bool flying;
	~entity();

protected:
	SDL_Rect drawRect;
};

