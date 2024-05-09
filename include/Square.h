//
// Created by mac on 2024/5/9.
//

#ifndef MAIN_SQUARE_H
#define MAIN_SQUARE_H

#include <SDL.h>

#include "game/GameObject.h"
#include "game/LTexture.h"

class Square : GameObject {

public :
    void init(int x, int y, int a, LTexture *texture, SDL_Rect *clip) override;

    void render() override;

    void update() override;

    void eventUpdate(SDL_Event* e) override;
};
#endif //MAIN_SQUARE_H
