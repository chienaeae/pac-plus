//
// Created by mac on 2024/5/9.
//

#ifndef MAIN_GAMEOBJECT_H
#define MAIN_GAMEOBJECT_H

#include <SDL.h>

#include "game/LTexture.h"

class GameObject {
protected:
    int velX;
    int velY;
    int velA;
    int x;
    int y;
    int a;

    SDL_Rect *clip;

    LTexture *texture;

public:
    GameObject() {
        velX = 0;
        velY = 0;
        velA = 0;
        x = 0;
        y = 0;
        a = 0;
        clip = nullptr;
        texture = nullptr;
    }

    virtual void init(int x, int y, int a, LTexture *t, SDL_Rect *clip);

    virtual void render();

    virtual void update();

    virtual void eventUpdate(SDL_Event* e);

};

#endif //MAIN_GAMEOBJECT_H
