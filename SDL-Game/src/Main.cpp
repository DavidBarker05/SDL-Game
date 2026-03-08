#include "Core/Game.h"

int main()
{
	Game game;
	if (game.Init()) game.Start();
}