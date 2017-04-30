#include "UIController.h"

std::vector<menuHandler> UIController::menus;

UIController::UIController()
{
}

void UIController::update()
{
	for (size_t x = 0; x < menus.size(); x++)
	{
		menus[x].update();
	}
}

void UIController::eventUpdate()
{
	for (size_t x = 0; x < menus.size(); x++)
	{
		menus[x].eventUpdate();
	}

	if (eventController::currentEvent.type == eventController::UIEvent)
	{
		hideAll();

		switch (eventController::currentEvent.user.code)
		{
		case eventController::showQuickplayMenu:
			menus[quickPlayMenu].visible = true;
			break;
		case eventController::showServerMenu:
			menus[serversMenu].visible = true;
			break;
		case eventController::showOptionsMenu:
			menus[optionsMenu].visible = true;
			break;
		}
	}
}

void UIController::draw()
{
	for (size_t x = 0; x < menus.size(); x++)
	{
		menus[x].draw();
	}
}

void UIController::registerMenu(menuHandler menu)
{
	menus.push_back(menu);
}

void UIController::hideAll()
{
	for (size_t x = 0; x < menus.size(); x++)
	{
		menus[x].visible = false;
	}
}

UIController::~UIController()
{
}
