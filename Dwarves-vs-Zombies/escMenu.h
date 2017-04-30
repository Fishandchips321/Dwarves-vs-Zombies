#pragma once
#include "action.h"
#include "UIController.h"
class escMenu :
	public action
{
public:
	escMenu();
	void keyDown();
	~escMenu();
};

