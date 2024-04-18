//
// Created by mac on 2024/4/10.
//

#include "game/FPS.h"

FPS::FPS() {
    mCountedFrames = 0;
    mCountedFramesInSecond = 0;
}

void FPS::start() {
    mFPSTimer.start();
}

void FPS::handleFrame() {
    mCapTimer.start();
    mCountedFrames++;
    Uint64 ticks = mFPSTimer.getTicks();
    if (ticks >= 1000) {
        mFPSTimer.start();
        mCountedFramesInSecond = mCountedFrames;
        mCountedFrames = 0;
    }
}

void FPS::cap() {
    int frameTicks = mCapTimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        //Wait remaining time
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}

int FPS::getFPS() {
    return mCountedFramesInSecond;
}