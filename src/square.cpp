//
// Created by mac on 2024/5/9.
//

#include "square.h"

#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_rect.h>

#include "game/texture.h"

void Square::init(int tX, int tY, int tAngle, Texture *tTexture, SDL_Rect *tClip) {
    mTexture = tTexture;
    mClip = tClip;

    mPosX = tX;
    mPosY = tY;
    mAngle = tAngle;

    mVelX = 0;
    mVelY = 0;
    mVelA = 0;
}

void Square::render(SDL_Renderer *tRenderer) {
    mTexture->Render(tRenderer, mPosX, mPosY, mClip, mAngle, 1.0f, 1.0f);
}

void Square::update(float /*deltaTime*/) {
    mPosX += mVelX;
    mPosY += mVelY;
    mAngle += mVelA;
}

void Square::eventUpdate(SDL_Event *tEvent) {
    if (tEvent->type == SDL_KEYDOWN) {
        switch (tEvent->key.keysym.sym) {
            case SDLK_RIGHT:
                mVelX = 3;
                break;
            case SDLK_LEFT:
                mVelX = -3;
                break;
            case SDLK_UP:
                mVelY = -3;
                break;
            case SDLK_DOWN:
                mVelY = 3;
                break;
            case SDLK_z:
                mVelA = -3;
                break;
            case SDLK_x:
                mVelA = 3;
                break;
            default:
                break;
        }
    } else if (tEvent->type == SDL_KEYUP) {
        switch (tEvent->key.keysym.sym) {
            case SDLK_RIGHT:
            case SDLK_LEFT:
                mVelX = 0;
                break;
            case SDLK_UP:
            case SDLK_DOWN:
                mVelY = 0;
                break;
            case SDLK_z:
            case SDLK_x:
                mVelA = 0;
                break;
            default:
                break;
        }
    }
}
