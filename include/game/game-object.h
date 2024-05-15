//
// Created by mac on 2024/5/9.
//

#ifndef MAIN_GAMEOBJECT_H
#define MAIN_GAMEOBJECT_H

#include <SDL.h>

#include "game/texture.h"

class GameObject {
   protected:
    int mVelX;
    int mVelY;
    int mVelA;
    int mPosX;
    int mPosY;
    int mAngle;

    SDL_Rect *mClip;

    Texture *mTexture;

   public:
    GameObject()
        : mVelX(),
          mVelY(),
          mVelA(),
          mPosX(),
          mPosY(),
          mAngle(),
          mClip(nullptr),
          mTexture(nullptr) {}

    virtual void init(int tX, int tY, int tA, Texture *tTexture, SDL_Rect *tClip) {};

    virtual void render() {};

    virtual void update(float tDeltaTime) {};

    virtual void lateUpdate(float tDeltaTime) {};

    virtual void eventUpdate(SDL_Event *tEvent) {};
};

#endif  // MAIN_GAMEOBJECT_H
