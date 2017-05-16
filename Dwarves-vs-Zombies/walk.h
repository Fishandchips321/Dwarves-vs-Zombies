#pragma once
#include "action.h"
#include "eventController.h"
class walk :
	public action
{
public:
	walk();
	void keyIsDown();
	~walk();
};

