//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include "game/texture.h"

class Sprite {
   public:
    Sprite();

    [[nodiscard]] auto getTextureRect() const -> const SDL_Rect &;

    [[nodiscard]] auto getTexture() const -> const Texture *;

    int getPositionX() const;

    int getPositionY() const;

    float getScaleX() const;

    float getScaleY() const;

    int getRotation() const;

    void setTextureRect(const SDL_Rect &tTextureRect);

    void setTexture(const Texture &tTexture, bool tResetRect = false);

    void setPosition(int tX, int tY);

    void move(int tOffsetX, int tOffsetY);

    void setScale(float tX, float tY);

    void scale(float tFactorX, float tFactorY);

    void setRotation(int tAngle);

    void rotate(int tAngle);

    void render(SDL_Renderer *tRenderer);

   private:
    int mPosX{0};
    int mPosY{0};

    float mScaleX{1.0f};
    float mScaleY{1.0f};

    int mAngle{0};

    SDL_Rect mTextureRect{};

    Texture mTexture{};
};

#endif  // MAIN_SPRITE_H
