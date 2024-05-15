//
// Created by mac on 2024/4/10.
//

#include "game/fps.h"

#include <SDL_stdinc.h>

#include <iostream>

#include "game/game.h"

FPS::FPS() {
    const int COLOR_R = 0;
    const int COLOR_G = 0;
    const int COLOR_B = 0;
    const int COLOR_A = 0xFF;

    mTextColor = {COLOR_R, COLOR_G, COLOR_B, COLOR_A};
}

void FPS::init() {
    mFPSTimer.start();
}

void FPS::update() {
    Uint64 const ticks = mFPSTimer.getTicks();
    if (ticks >= MILLISECOND) {
        mFPSTimer.start();
        mCountedFramesInSecond = mCountedFrames;
        mCountedFrames = 0;
    }
}

void FPS::renderUpdate() {
    // increment count by 1 per render frame
    mCountedFrames++;

    // 1. Prepare FPS text to be rendered
    mTimeText.str("");
    mTimeText << "FPS: " << mCountedFramesInSecond;
    if (!mTextTexture.LoadFromRenderedText(mTimeText.str(), mTextColor)) {
        std::cout << "Unable to render FPS texture!\n";
    }
    // 2. Render textures
    const int OFFSET_X = 20;
    const int OFFSET_Y = 20;
    mTextTexture.Render(SCREEN_WIDTH - mTextTexture.GetWidth() - OFFSET_X, OFFSET_Y);
}
