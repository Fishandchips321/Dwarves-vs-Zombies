#include "UIController.h"

std::vector<menuHandler> UIController::menus;
int UIController::focus; //which menu has focus. 0 for the game screen

UIController::UIController()
{
}

void UIController::update()
{
	menus[focus].update();
}

void UIController::eventUpdate()
{
	menus[focus].eventUpdate();

	if (eventController::currentEvent.type == eventController::UIEvent)
	{
		if (eventController::currentEvent.user.code == eventController::showMenu)
		{
			if (menus.size() < *(size_t*)eventController::currentEvent.user.data1)
			{
				focus = *(int*)eventController::currentEvent.user.data1;
			}
		}
		
	}
}

void UIController::draw()
{
	menus[focus].draw();
}

void UIController::registerMenu(menuHandler menu)
{
	menus.push_back(menu);
}

int UIController::getFocus()
{
	return focus;
}

bool UIController::showMenu(int menu)
{
	if(menu > maxMenus)
		return false;
	menus[menu].loseFocus();
	focus = menu;
	return true;
}

UIController::~UIController()
{
}
