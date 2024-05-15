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

#include <cstdio>
#include <memory>

#include "SceneTest.h"
#include "game/Core.h"
#include "game/Font.h"
#include "game/SceneStateMachine.h"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
Font gFont = {};

bool Game::Init() {
    bool success = true;

    // Init SDL SubSystems (Video)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialized! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL_image for PNG loading
    int const imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) == 0) {
        printf("SDL_image count not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // Init SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    // Init SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    success = gFont.LoadFromFile("assets/font/RedditSans-Regular.ttf");
    if (!success) {
        printf("Global Font could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL Window
    gWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL Renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    std::shared_ptr<SceneTest> const testScene =
        std::make_shared<SceneTest>(sceneStateMachine, textureAllocator);

    unsigned int const testSceneID = sceneStateMachine.Add(testScene);

    sceneStateMachine.SwitchTo(testSceneID);

    clock.start();

    return success;
}

void Game::Run() {
    quit = false;
    Uint64 current = clock.getTicks();
    Uint64 previous = current;
    Uint64 lag = 0;
    fps.init();

    while (!quit) {
        current = clock.getTicks();
        Uint64 const elapsed = current - previous;
        deltaTime = (float)elapsed / MILLISECOND;

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
    sceneStateMachine.Update(deltaTime);
}

void Game::lateUpdate() {
    sceneStateMachine.LateUpdate(deltaTime);
}

void Game::eventUpdate() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        sceneStateMachine.EventUpdate(&e);
    }
}

void Game::renderUpdate() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // FPS handle each render update
    fps.update();

    // test object handle each render update
    sceneStateMachine.RenderUpdate();

    SDL_RenderPresent(gRenderer);
}
