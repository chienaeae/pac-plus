//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include "game/texture.h"

class Sprite {
   public:
    Sprite();

    [[nodiscard]] auto getTextureRect() const -> const SDL_Rect&;

    [[nodiscard]] auto getTexture() const -> const Texture*;

    [[nodiscard]] auto getPositionX() const -> int;

    [[nodiscard]] auto getPositionY() const -> int;

    [[nodiscard]] auto getScaleX() const -> float;

    [[nodiscard]] auto getScaleY() const -> float;

    [[nodiscard]] auto getRotation() const -> int;

    void setTextureRect(const SDL_Rect& tTextureRect);

    void setTexture(const Texture& tTexture, bool tResetRect = false);

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

    Texture mTexture;
};

#endif  // MAIN_SPRITE_H
