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
    int posX;
    int posY;
    int angle;

    SDL_Rect *clip;

    LTexture *texture;

public:
    GameObject() : velX(), velY(), velA(), posX(), posY(), angle(), clip(nullptr), texture(nullptr){}

    virtual void init(int x, int y, int a, LTexture *t, SDL_Rect *c) {};

    virtual void render() {};

    virtual void update(float deltaTime) {};

    virtual void lateUpdate(float deltaTime) {};

    virtual void eventUpdate(SDL_Event* e) {};

};

#endif //MAIN_GAMEOBJECT_H
