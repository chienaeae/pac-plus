//
// Created by mac on 2024/5/11.
//

#include "game/component-keyboard-movement.h"

#include <SDL_events.h>
#include <SDL_keycode.h>

#include <iostream>

#include "game/component-animation.h"
#include "game/component.h"

ComponentKeyboardMovement::ComponentKeyboardMovement(Object *tOwner)
    : Component(tOwner), mMoveSpeed(3), mVelX(0), mVelY(0), mPressedCount(0) {}

void ComponentKeyboardMovement::Awake() {
    mAnimation = mOwner->GetComponent<ComponentAnimation>();
}

void ComponentKeyboardMovement::SetSpeed(int tSpeed) {
    mMoveSpeed = tSpeed;
}

void ComponentKeyboardMovement::Update(float /*deltaTime*/) {
    mOwner->Transform->AddPosition(mVelX, mVelY);
}

void ComponentKeyboardMovement::EventUpdate(SDL_Event *tEvent) {
    if (tEvent->type == SDL_KEYDOWN) {
        mAnimation->SetAnimationState(AnimationState::Walk);
        switch (tEvent->key.keysym.sym) {
            case SDLK_RIGHT:
                mVelX = mMoveSpeed;
                mVelY = 0;
                mAnimation->SetAnimationDirection(FacingDirection::Right);
                break;
            case SDLK_LEFT:
                mVelX = -mMoveSpeed;
                mVelY = 0;
                mAnimation->SetAnimationDirection(FacingDirection::Left);
                break;
            case SDLK_UP:
                mVelX = 0;
                mVelY = -mMoveSpeed;
                mAnimation->SetAnimationDirection(FacingDirection::Up);
                break;
            case SDLK_DOWN:
                mVelX = 0;
                mVelY = mMoveSpeed;
                mAnimation->SetAnimationDirection(FacingDirection::Down);
                break;
            default:
                break;
        }
    } else if (tEvent->type == SDL_KEYUP) {
        switch (tEvent->key.keysym.sym) {
            case SDLK_RIGHT:
            case SDLK_LEFT:
                if (mPressedCount == 0) {
                    mAnimation->SetAnimationState(AnimationState::Idle);
                    mVelX = 0;
                }
                break;
            case SDLK_UP:
            case SDLK_DOWN:
                if (mPressedCount == 0) {
                    mAnimation->SetAnimationState(AnimationState::Idle);
                    mVelY = 0;
                }
                break;
            default:
                break;
        }
    }
}
