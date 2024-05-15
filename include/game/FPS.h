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
    int mCountedFrames{0};
    int mCountedFramesInSecond{0};

    SDL_Color mTextColor{};
    LTexture mTextTexture;
    std::stringstream mTimeText;
};

#endif  // MAIN_FPS_H
