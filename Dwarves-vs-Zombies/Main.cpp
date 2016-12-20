#include "game.h"
#include <iostream>
#include <SDL.h>
#undef main
int main()
{
	game gameOb;

	gameOb.init();
	gameOb.startGameLoop();

	return 0;
}