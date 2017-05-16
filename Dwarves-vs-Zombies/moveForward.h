#pragma once
#include "action.h"
#include "eventController.h"
class moveForward :
	public action
{
public:
	moveForward();
	void keyIsDown();
	~moveForward();
};

