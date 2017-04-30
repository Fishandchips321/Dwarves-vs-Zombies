#pragma once
#include "windowRenderer.h"
#include <vector>
class windowController
{
public:
	windowController();
	static windowRenderer* registerWindow(int w, int h, std::string name);
	~windowController();

private:
	static std::vector<windowRenderer* > windows;
};

