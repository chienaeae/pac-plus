//
// Created by mac on 2024/5/9.
//

#ifndef MAIN_SQUARE_H
#define MAIN_SQUARE_H

#include <SDL.h>

#include "game/game-object.h"
#include "game/texture.h"

class Square : public GameObject {
   public:
    void init(int tX, int tY, int tA, Texture *tTexture, SDL_Rect *tClip) override;

    void render() override;

    void update(float tDeltaTime) override;

    void eventUpdate(SDL_Event *tEvent) override;
};
#endif  // MAIN_SQUARE_H
