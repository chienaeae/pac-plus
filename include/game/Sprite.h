//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include "game/LTexture.h"

class Sprite {
   public:
    Sprite();

    const SDL_Rect& getTextureRect() const;

    const LTexture* getTexture() const;

    int getPositionX() const;

    int getPositionY() const;

    float getScaleX() const;

    float getScaleY() const;

    int getRotation() const;

    void setTextureRect(const SDL_Rect& tr);

    void setTexture(const LTexture& t, bool resetRect = false);

    void setPosition(int x, int y);

    void move(int offsetX, int offsetY);

    void setScale(float x, float y);

    void scale(float factorX, float factorY);

    void setRotation(int a);

    void rotate(int a);

    void render();

   private:
    int posX;
    int posY;

    float scaleX;
    float scaleY;

    int angle;

    SDL_Rect textureRect;

    LTexture texture;
};

#endif  // MAIN_SPRITE_H
