#include <cstdlib>
#define SDL_MAIN_HANDLED

#include <cstdio>

#include "game/Game.h"

using namespace std;

int main(int /*argc*/, char* /*argv*/[]) {
    Game game;
    if (!game.Init()) {
        printf("Failed to initialize!\n");
        Game::Close();
        return EXIT_FAILURE;
    }

    game.Run();
    Game::Close();
    return EXIT_SUCCESS;
}
