//
// Created by mac on 2024/5/11.
//

#include <SDL.h>

#include "game/GameObject.h"
#include "game/LTexture.h"

void GameObject::init(int x, int y, int a, LTexture *texture, SDL_Rect *clip){
    this->texture = texture;
    this->clip = clip;

    this->x = x;
    this->y = y;
    this->a = a;

    this->velX = 0;
    this->velY = 0;
    this->velA = 0;
}

void GameObject::render() {
    this->texture->render(this->x, this->y, clip, this->a);
}

void GameObject::update() {
    this->x += this->velX;
    this->y += this->velY;
    this->a += this->velA;

}

void GameObject::eventUpdate(SDL_Event* e) {
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
        }
    }
    else if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
                velX = 0;
                break;
            case SDLK_LEFT:
                velX = 0;
                break;
            case SDLK_UP:
                velY = 0;
                break;
            case SDLK_DOWN:
                velY = 0;
                break;
            case SDLK_z:
                velA = 0;
                break;
            case SDLK_x:
                velA = 0;
                break;
        }
    }
}
