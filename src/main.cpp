#define SDL_MAIN_HANDLED

#include <cstdio>

#include "game/Game.h"

using namespace std;

int main(int argc, char *argv[])
{
    Game game;
    if (!game.Init())
    {
        printf("Failed to initialize!\n");
        game.Close();
        return EXIT_FAILURE;
    }

    game.Run();
    game.Close();
    return EXIT_SUCCESS;
}
