#include "windowController.h"

std::vector<windowRenderer* > windowController::windows;

windowController::windowController()
{
}

windowRenderer * windowController::registerWindow(int w, int h, std::string name)
{

	windowRenderer* window = new windowRenderer;
	if (!window->init(name, w, h))
	{
		std::cout << "[ERROR]: Couldn't create window \"" << name.c_str() << "\"" << std::endl;
	}
	else
	{
		windows.push_back(window);
	}

	return window;
}


windowController::~windowController()
{
	for (size_t x = 0; x < windows.size(); x++)
	{
		delete windows[x];
		windows[x] = nullptr;
	}
}
