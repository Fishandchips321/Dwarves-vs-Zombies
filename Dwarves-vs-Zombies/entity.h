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
	bool flying;
	~entity();

	int runVel = 0, sprintVel = 0, walkVel = 0, movVel = runVel;

protected:
	SDL_Rect drawRect;
	
};

