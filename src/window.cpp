//
// Created by mac on 5/15/24.
//

#include "game/window.h"

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include <iostream>

#include "game/font.h"

SDL_Renderer* gRenderer = nullptr;
Font gFont = {};

Window::Window() : mWindow(nullptr), mIsOpen(false) {}

auto Window::Init(const std::string& tName, int tWidth, int tHeight) -> int {
    bool success = true;

    // Init SDL Window
    mWindow = SDL_CreateWindow(tName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               tWidth, tHeight, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    } else {
        mIsOpen = true;
    }

    // Init SDL Renderer
    gRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Init SDL SubSystems (Video)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialized! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Init SDL_image for PNG loading
    int const imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) == 0) {
        std::cout << "SDL_image count not initialize! SDL_image Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Init SDL_mixer
    const int FREQUENCY = 44100;
    const int CHANNEL = 2;
    const int CHUNK_SIZE = 2048;
    if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, CHANNEL, CHUNK_SIZE) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Init SDL_ttf
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << SDL_GetError() << "\n";
        return false;
    }
    success = gFont.LoadFromFile("assets/font/RedditSans-Regular.ttf");
    if (!success) {
        std::cout << "Global Font could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    return success;
}

void Window::BeginDraw() {
    const int COLOR_R = 0xFF;
    const int COLOR_G = 0xFF;
    const int COLOR_B = 0xFF;
    const int COLOR_A = 0xFF;
    SDL_SetRenderDrawColor(gRenderer, COLOR_R, COLOR_G, COLOR_B, COLOR_A);
    SDL_RenderClear(gRenderer);
}

void Window::Draw() {
    SDL_RenderPresent(gRenderer);
}

void Window::EndDraw() {}

auto Window::GetRenderer() -> SDL_Renderer* {
    return gRenderer;
}

void Window::Close() {
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    mIsOpen = false;
}

auto Window::IsOpen() const -> bool {
    return mIsOpen;
}
