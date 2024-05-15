//
// Created by mac on 2024/5/11.
//

#include "game/Game.h"

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include <iostream>
#include <memory>

#include "SceneTest.h"
#include "game/Core.h"
#include "game/Font.h"
#include "game/SceneStateMachine.h"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
Font gFont = {};

auto Game::Init() -> bool {
    bool success = true;

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

    // Init SDL Window
    gWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Init SDL Renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    std::shared_ptr<SceneTest> const testScene =
        std::make_shared<SceneTest>(mSceneStateMachine, mTextureAllocator);

    unsigned int const testSceneID = mSceneStateMachine.Add(testScene);

    mSceneStateMachine.SwitchTo(testSceneID);

    mClock.start();

    return success;
}

void Game::Run() {
    mQuit = false;
    Uint64 current = mClock.getTicks();
    Uint64 previous = current;
    Uint64 lag = 0;
    mFPS.init();

    while (!mQuit) {
        current = mClock.getTicks();
        Uint64 const elapsed = current - previous;
        mDeltaTime = static_cast<float>(elapsed) / MILLISECOND;

        lag += elapsed;
        eventUpdate();
        while (lag >= TICKS_PER_GAME_FRAME) {
            update();
            lateUpdate();
            lag -= TICKS_PER_GAME_FRAME;
        }
        renderUpdate();

        previous = current;
    }
}

void Game::Close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::update() {
    mSceneStateMachine.Update(mDeltaTime);
}

void Game::lateUpdate() {
    mSceneStateMachine.LateUpdate(mDeltaTime);
}

void Game::eventUpdate() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            mQuit = true;
        }
        mSceneStateMachine.EventUpdate(&e);
    }
}

void Game::renderUpdate() {
    const int COLOR_R = 0xFF;
    const int COLOR_G = 0xFF;
    const int COLOR_B = 0xFF;
    const int COLOR_A = 0xFF;
    SDL_SetRenderDrawColor(gRenderer, COLOR_R, COLOR_G, COLOR_B, COLOR_A);
    SDL_RenderClear(gRenderer);

    // FPS handle each render update
    mFPS.update();

    // test object handle each render update
    mSceneStateMachine.RenderUpdate();

    SDL_RenderPresent(gRenderer);
}
