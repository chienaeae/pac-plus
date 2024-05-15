//
// Created by mac on 2024/4/10.
//

#include "game/FPS.h"

#include <SDL_stdinc.h>

#include <cstdio>
#include <iostream>

#include "game/Game.h"

FPS::FPS() {
    const int COLOR_R = 255;
    const int COLOR_G = 255;
    const int COLOR_B = 255;
    const int COLOR_A = 255;

    textColor = {COLOR_R, COLOR_G, COLOR_B, COLOR_A};
}

void FPS::init() {
    mFPSTimer.start();
}

void FPS::update() {
    // update frame per second
    mCountedFrames++;
    Uint64 const ticks = mFPSTimer.getTicks();
    if (ticks >= MILLISECOND) {
        mFPSTimer.start();
        mCountedFramesInSecond = mCountedFrames;
        mCountedFrames = 0;
    }

    // Render
    // 1. Prepare FPS text to be rendered
    timeText.str("");
    timeText << "FPS: " << mCountedFramesInSecond;
    if (!textTexture.LoadFromRenderedText(timeText.str(), textColor)) {
        std::cout << "Unable to render FPS texture!\n";
    }
    // 2. Render textures
    const int OFFSET_X = 20;
    const int OFFSET_Y = 20;
    textTexture.Render(SCREEN_WIDTH - textTexture.GetWidth() - OFFSET_X, OFFSET_Y);
}
