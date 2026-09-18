#include "config.h"
#include "Game/Game.h"
#include "Types.h"

int main(int argc, char** argv)
{
    CSTRING executablePath = argv[0];
    Game game;
    if (game.Init(executablePath, COMPANY_NAME, PRODUCT_NAME, EXECUTABLE_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT))
        game.Start();
    game.Shutdown(); // Game has finished running
}
