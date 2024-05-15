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
    // increment count by 1 per game frame
    mCountedGameFrames++;

    Uint64 const ticks = mFPSTimer.getTicks();
    if (ticks >= MILLISECOND) {
        mRenderText.str("");
        mRenderText << "Render FPS: " << mCountedRenderFrames;
        mGameText.str("");
        mGameText << "Game FPS: " << mCountedGameFrames;

        if (!mGameRenderTexture.LoadFromRenderedText(mGameText.str(), mTextColor) ||
            !mTextTexture.LoadFromRenderedText(mRenderText.str(), mTextColor)) {
            std::cout << "Unable to render FPS texture!\n";
        } else {
        }

        mCountedGameFrames = 0;
        mCountedRenderFrames = 0;
        mFPSTimer.start();
    }
}

void FPS::renderUpdate() {
    // increment count by 1 per render frame
    mCountedRenderFrames++;

    // 1. Prepare FPS text to be rendered
    const int OFFSET_X = 20;
    const int OFFSET_Y = 20;

    // 2. Render textures
    mGameRenderTexture.Render(SCREEN_WIDTH - mGameRenderTexture.GetWidth() - OFFSET_X, OFFSET_Y);
    mTextTexture.Render(SCREEN_WIDTH - mTextTexture.GetWidth() - OFFSET_X, OFFSET_Y * 3);
}
