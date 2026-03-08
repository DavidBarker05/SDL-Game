#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	if (game.Init()) game.Start();
	return 0;
}
