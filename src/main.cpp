#define SDL_MAIN_HANDLED

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "game/game.h"

auto main(int /*argc*/, char* /*argv*/[]) -> int {
    Game game;
    if (!game.Init()) {
        std::cout << "Failed to initialize!\n";
        Game::Close();
        return EXIT_FAILURE;
    }

    game.Run();
    Game::Close();
    return EXIT_SUCCESS;
}
