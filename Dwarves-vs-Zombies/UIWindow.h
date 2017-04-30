#pragma once
#include "windowController.h"
#include "windowRenderer.h"
class UIWindow
{
public:
	UIWindow();
	virtual void update();
	virtual void eventUpdate();
	virtual void draw();
	~UIWindow();
protected:
	windowRenderer* renderer;
};

