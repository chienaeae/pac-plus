//
// Created by mac on 2024/5/9.
//

#include "Square.h"

#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_rect.h>

#include "game/LTexture.h"

void Square::init(int x, int y, int a, LTexture *texture, SDL_Rect *clip) {
    this->texture = texture;
    this->clip = clip;

    this->posX = x;
    this->posY = y;
    this->angle = a;

    this->velX = 0;
    this->velY = 0;
    this->velA = 0;
}

void Square::render() {
    this->texture->Render(this->posX, this->posY, clip, this->angle, 1.0f, 1.0f);
}

void Square::update(float /*deltaTime*/) {
    this->posX += this->velX;
    this->posY += this->velY;
    this->angle += this->velA;
}

void Square::eventUpdate(SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
                velX = 3;
                break;
            case SDLK_LEFT:
                velX = -3;
                break;
            case SDLK_UP:
                velY = -3;
                break;
            case SDLK_DOWN:
                velY = 3;
                break;
            case SDLK_z:
                velA = -3;
                break;
            case SDLK_x:
                velA = 3;
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
            case SDLK_z:
            case SDLK_x:
                velA = 0;
                break;
            default:
                break;
        }
    }
}
