//
// Created by mac on 2024/5/11.
//

#include "game/component-keyboard-movement.h"

#include <SDL_events.h>
#include <SDL_keycode.h>

#include "game/component.h"

ComponentKeyboardMovement::ComponentKeyboardMovement(Object *tOwner)
    : Component(tOwner), mMoveSpeed(3), mVelX(0), mVelY(0) {}

void ComponentKeyboardMovement::SetSpeed(int tSpeed) {
    mMoveSpeed = tSpeed;
}

void ComponentKeyboardMovement::Update(float /*deltaTime*/) {
    mOwner->Transform->AddPosition(mVelX, mVelY);
}

void ComponentKeyboardMovement::EventUpdate(SDL_Event *tEvent) {
    if (tEvent->type == SDL_KEYDOWN) {
        switch (tEvent->key.keysym.sym) {
            case SDLK_RIGHT:
                mVelX = mMoveSpeed;
                break;
            case SDLK_LEFT:
                mVelX = -mMoveSpeed;
                break;
            case SDLK_UP:
                mVelY = -mMoveSpeed;
                break;
            case SDLK_DOWN:
                mVelY = mMoveSpeed;
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
            default:
                break;
        }
    }
}
