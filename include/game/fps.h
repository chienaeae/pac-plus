//
// Created by mac on 2024/4/10.
//

#ifndef MAIN_FPS_H
#define MAIN_FPS_H

#include "texture.h"
#include "timer.h"

class FPS {
   public:
    FPS();

    void init();

    void update();

    void renderUpdate(SDL_Renderer* tRenderer);

   private:
    void process();

    Timer mFPSTimer;

    std::stringstream mRenderText;
    int mCountedRenderFrames{0};

    std::stringstream mGameText;
    int mCountedGameFrames{0};

    SDL_Color mTextColor{};
    Texture mTextTexture;
    Texture mGameRenderTexture;
};

#endif  // MAIN_FPS_H
