//
// Created by mac on 2024/5/11.
//

#include "game/game.h"

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include <iostream>
#include <memory>

#include "game/core.h"
#include "scene-test.h"

auto Game::Init() -> bool {
    if (!mWindow.Init("Example", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        close();
        return false;
    }
    return true;
}

void Game::Run() {
    mQuit = false;
    Uint64 current = mClock.getTicks();
    Uint64 previous = current;
    Uint64 lag = 0;

    mFPS.init();
    mClock.start();

    OnCreate();
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
    close();
}

void Game::close() {
    mWindow.Close();
}

void Game::update() {
    mFPS.update();
    Update(mDeltaTime);
}

void Game::lateUpdate() {
    LateUpdate(mDeltaTime);
}

void Game::eventUpdate() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            mQuit = true;
        }
        EventUpdate(&e);
    }
}

void Game::renderUpdate() {
    mWindow.BeginDraw();

    SDL_Renderer* renderer = mWindow.GetRenderer();
    mFPS.renderUpdate(renderer);
    RenderUpdate(renderer);

    mWindow.Draw();
    mWindow.EndDraw();
}

auto Game::IsRunning() const -> bool {
    return mQuit;
}
