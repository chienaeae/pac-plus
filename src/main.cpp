#define SDL_MAIN_HANDLED

#include <cstdlib>
#include <iostream>

#include "pac-plus.h"

auto main(int /*argc*/, char* /*argv*/[]) -> int {
    PacPlus game;
    if (!game.Init()) {
        std::cout << "Failed to initialize!\n";
        return EXIT_FAILURE;
    }

    game.Run();
    return EXIT_SUCCESS;
}
