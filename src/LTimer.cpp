//
// Created by mac on 2024/4/10.
//

#include "game/LTimer.h"

#include <SDL_stdinc.h>
#include <SDL_timer.h>

LTimer::LTimer() {
    mStartTicks = 0;
    mPausedTicks = 0;
    mStarted = false;
    mPaused = false;
}

void LTimer::start() {
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks64();
    mPausedTicks = 0;
}

void LTimer::stop() {
    mStartTicks = 0;
    mPausedTicks = 0;
    mStarted = false;
    mPaused = false;
}

void LTimer::pause() {
    if (mStarted && !mPaused) {
        mPaused = true;

        mPausedTicks = SDL_GetTicks64() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause() {
    if (mStarted && mPaused) {
        mPaused = false;

        mStartTicks = SDL_GetTicks64() - mPausedTicks;
        mPausedTicks = 0;
    }
}

Uint64 LTimer::getTicks() const {
    Uint64 time = 0;

    if (mStarted) {
        if (mPaused) {
            time = mPausedTicks;
        } else {
            time = SDL_GetTicks64() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted() const {
    return mStarted;
}

bool LTimer::isPaused() const {
    return mPaused && mStarted;
}
