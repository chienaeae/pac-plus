//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <SDL.h>

#include "game/Core.h"
#include "game/FPS.h"
#include "game/LTimer.h"
#include "game/ResourceAllocator.h"
#include "game/SceneStateMachine.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

const int GAME_FRAME = 60;
const int TICKS_PER_GAME_FRAME = SECOND * MILLISECOND / GAME_FRAME;

class Game {
   public:
    bool Init();

    void Run();

    static void Close();

   private:
    // update: This is where most of the game logic will go;
    // including: movement, AI, and animation updates
    void update();

    // lateUpdate: Any logic that relies on data calculated
    // in the Update method will go here, for example: you
    // could place collision logic here that checks for
    // collisions once every entities position has been
    // updated in the Update method
    void lateUpdate();

    void eventUpdate();

    void renderUpdate();

    FPS mFPS;

    SceneStateMachine mSceneStateMachine;

    ResourceAllocator<LTexture> mTextureAllocator;

    LTimer mClock;

    // deltaTime: It records the last game loop update as seconds
    float mDeltaTime;

    bool mQuit;
};

#endif  // MAIN_GAME_H
