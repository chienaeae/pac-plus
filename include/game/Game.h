//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <SDL.h>

#include "game/FPS.h"
#include "game/SceneStateMachine.h"
#include "game/LTimer.h"


const int GAME_FRAME = 60;

const int SECOND = 1000;
const int TICKS_PER_GAME_FRAME = SECOND / GAME_FRAME;


class Game {
public:
    bool Init();

    void Run();

    void Close();

private:
    void update();

    void eventUpdate(SDL_Event* e);

    void renderUpdate();

    FPS fps;

    SceneStateMachine sceneStateMachine;

    LTimer clock;
    // deltaTime records the last game loop update as seconds
    float deltaTime;
};

#endif //MAIN_GAME_H
