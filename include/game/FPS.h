//
// Created by mac on 2024/4/10.
//

#ifndef MAIN_FPS_H
#define MAIN_FPS_H

#include "LTexture.h"
#include "LTimer.h"

class FPS {
   public:
    FPS();

    void init();

    void update();

   private:
    LTimer mFPSTimer;
    int mCountedFrames;
    int mCountedFramesInSecond;

    SDL_Color textColor;
    LTexture textTexture;
    std::stringstream timeText;
};

#endif  // MAIN_FPS_H
