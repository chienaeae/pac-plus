//
// Created by mac on 2024/4/10.
//

#include "game/timer.h"

#include <SDL_stdinc.h>
#include <SDL_timer.h>

Timer::Timer() = default;

void Timer::start() {
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks64();
    mPausedTicks = 0;
}

void Timer::stop() {
    mStartTicks = 0;
    mPausedTicks = 0;
    mStarted = false;
    mPaused = false;
}

void Timer::pause() {
    if (mStarted && !mPaused) {
        mPaused = true;

        mPausedTicks = SDL_GetTicks64() - mStartTicks;
        mStartTicks = 0;
    }
}

void Timer::unpause() {
    if (mStarted && mPaused) {
        mPaused = false;

        mStartTicks = SDL_GetTicks64() - mPausedTicks;
        mPausedTicks = 0;
    }
}

auto Timer::getTicks() const -> Uint64 {
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

auto Timer::isStarted() const -> bool {
    return mStarted;
}

auto Timer::isPaused() const -> bool {
    return mPaused && mStarted;
}
