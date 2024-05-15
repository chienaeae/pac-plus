//
// Created by mac on 2024/5/11.
//

#include "game/ComponentKeyboardMovement.h"

#include <SDL_events.h>
#include <SDL_keycode.h>

#include "game/Component.h"
#include "game/Object.h"

ComponentKeyboardMovement::ComponentKeyboardMovement(Object *owner)
    : Component(owner), moveSpeed(3), velX(0), velY(0) {}

void ComponentKeyboardMovement::SetSpeed(int speed) {
    moveSpeed = speed;
}

void ComponentKeyboardMovement::Update(float /*deltaTime*/) {
    owner->transform->AddPosition(velX, velY);
}

void ComponentKeyboardMovement::EventUpdate(SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
                velX = moveSpeed;
                break;
            case SDLK_LEFT:
                velX = -moveSpeed;
                break;
            case SDLK_UP:
                velY = -moveSpeed;
                break;
            case SDLK_DOWN:
                velY = moveSpeed;
                break;
            default:
                break;
        }
    } else if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
            case SDLK_LEFT:
                velX = 0;
                break;
            case SDLK_UP:
            case SDLK_DOWN:
                velY = 0;
                break;
            default:
                break;
        }
    }
}
