#include "config.h"
#include "Game/Game.h"

int main()
{
    Game game;
    if (game.Init(COMPANY_NAME, PRODUCT_NAME, EXECUTABLE_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT))
        game.Start();
    game.Shutdown(); // Game has finished running
}
