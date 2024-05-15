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

    void setTextureRect(const SDL_Rect& tTextureRect);

    void setTexture(const LTexture& tTexture, bool tResetRect = false);

    void setPosition(int tX, int tY);

    void move(int tOffsetX, int tOffsetY);

    void setScale(float tX, float tY);

    void scale(float tFactorX, float tFactorY);

    void setRotation(int tAngle);

    void rotate(int tAngle);

    void render();

   private:
    int mPosX;
    int mPosY;

    float mScaleX;
    float mScaleY;

    int mAngle;

    SDL_Rect mTextureRect;

    LTexture mTexture;
};

#endif  // MAIN_SPRITE_H
