#pragma once
#include "action.h"
#include "eventController.h"
class moveRight :
	public action
{
public:
	moveRight();
	void keyIsDown();
	~moveRight();
};

