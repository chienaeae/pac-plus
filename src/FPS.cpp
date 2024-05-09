//
// Created by mac on 2024/4/10.
//

#include "game/FPS.h"
#include "game/Core.h"

FPS::FPS() {
    mCountedFrames = 0;
    mCountedFramesInSecond = 0;

    textColor = {0, 0, 0, 255};
}

void FPS::init() {
    mFPSTimer.start();
}

void FPS::update() {
    // update frame per second
    mCountedFrames++;
    Uint64 ticks = mFPSTimer.getTicks();
    if (ticks >= 1000) {
        mFPSTimer.start();
        mCountedFramesInSecond = mCountedFrames;
        mCountedFrames = 0;
    }

    // Render
    // 1. Prepare FPS text to be rendered
    timeText.str("");
    timeText << "FPS: " << mCountedFramesInSecond;
    if (!textTexture.loadFromRenderedText(timeText.str(), textColor))
    {
        printf("Unable to render FPS texture!\n");
    }
    // 2. Render textures
    textTexture.render(SCREEN_WIDTH - textTexture.getWidth() - 20, 20);
}
