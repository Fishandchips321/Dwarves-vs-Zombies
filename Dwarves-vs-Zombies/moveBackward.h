#pragma once
#include "action.h"
#include "eventController.h"
class moveBackward :
	public action
{
public:
	moveBackward();
	void keyIsDown();
	~moveBackward();
};

