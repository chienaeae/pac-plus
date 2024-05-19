//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include "game/texture.h"

class Sprite {
   public:
    Sprite();

    [[nodiscard]] auto GetTextureRect() const -> const SDL_Rect &;

    [[nodiscard]] auto GetTexture() const -> const Texture *;

    int GetPositionX() const;

    int GetPositionY() const;

    float GetScaleX() const;

    float GetScaleY() const;

    int GetRotation() const;

    void SetTextureRect(const SDL_Rect &tTextureRect);

    void SetTexture(const Texture &tTexture, bool tResetRect = false);

    void SetPosition(int tX, int tY);

    void Move(int tOffsetX, int tOffsetY);

    void SetScale(float tX, float tY);

    void Scale(float tFactorX, float tFactorY);

    void SetRotation(int tAngle);

    void Rotate(int tAngle);

    void Render(SDL_Renderer *tRenderer);

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
