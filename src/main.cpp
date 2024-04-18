#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "game/Core.h"
#include "game/FPS.h"
#include "game/LTexture.h"

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gFont = nullptr;

bool init();

void close();

int main(int argc, char *argv[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
        close();
        return EXIT_FAILURE;
    }
    SDL_Color textColor = {0, 0, 0, 255};
    LTexture gFPSTextTexture;
    std::stringstream timeText;

    FPS fps;
    fps.start();

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // FPS handle every frames
        fps.handleFrame();
        // Prepare FPS text to be rendered
        timeText.str("");
        timeText << "FPS: " << fps.getFPS();
        if (!gFPSTextTexture.loadFromRenderedText(timeText.str(), textColor))
        {
            printf("Unable to render FPS texture!\n");
        }
        // Render textures
        gFPSTextTexture.render(SCREEN_WIDTH - gFPSTextTexture.getWidth() - 20, 20);

        SDL_RenderPresent(gRenderer);
        fps.cap();
    }
    close();
    return EXIT_SUCCESS;
}

bool init()
{
    bool success = true;

    // Init SDL SubSystems (Video)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialized! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL_image for PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image count not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // Init SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    // Init SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    gFont = TTF_OpenFont("assets/font/lazy.ttf", 28);

    // Init SDL Window
    gWindow = SDL_CreateWindow(
        "Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL Renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
