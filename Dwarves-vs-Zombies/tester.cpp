#include "tester.h"



tester::tester()
{
}

void tester::init()
{
	testText = imageService::loadTexture("assets/textures/tester.png");

	rect.x = rect.y = 0;
	rect.w = render::screenWidth;
	rect.h = render::screenHeight;
}

void tester::draw()
{
	render::drawTexture(testText, &rect);
}

tester::~tester()
{
}
