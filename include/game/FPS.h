//
// Created by mac on 2024/4/10.
//

#ifndef MAIN_FPS_H
#define MAIN_FPS_H

#include "LTimer.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class FPS {
public:
    FPS();

    void start();

    void handleFrame();

    void cap();

    int getFPS();

private:
    LTimer mFPSTimer;
    LTimer mCapTimer;
    int mCountedFrames;
    int mCountedFramesInSecond;
};

#endif //MAIN_FPS_H
