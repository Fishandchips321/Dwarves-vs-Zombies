#pragma once
#include "action.h"
#include "eventController.h"
class moveLeft :
	public action
{
public:
	moveLeft();
	void keyIsDown();
	~moveLeft();
};

