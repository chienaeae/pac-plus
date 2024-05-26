//
// Created by mac on 2024/5/11.
//

#include "game/sprite.h"

#include "game/texture.h"

Sprite::Sprite() = default;

auto Sprite::GetTextureRect() const -> const SDL_Rect& {
    return mTextureRect;
}

auto Sprite::GetTexture() const -> const Texture* {
    return &mTexture;
}

auto Sprite::GetPositionX() const -> int {
    return mPosX;
}

auto Sprite::GetPositionY() const -> int {
    return mPosY;
}

auto Sprite::GetScaleX() const -> float {
    return mScaleX;
}

auto Sprite::GetScaleY() const -> float {
    return mScaleY;
}

auto Sprite::GetRotation() const -> int {
    return mAngle;
}

void Sprite::SetTextureRect(const SDL_Rect& tTextureRect) {
    mTextureRect = tTextureRect;
}

void Sprite::SetTexture(const Texture& tTexture) {
    mTexture = tTexture;
}

void Sprite::SetPosition(int tX, int tY) {
    mPosX = tX;
    mPosY = tY;
}

void Sprite::Move(int tOffsetX, int tOffsetY) {
    mPosX += tOffsetX;
    mPosY += tOffsetY;
}

void Sprite::SetScale(float tX, float tY) {
    mScaleX = tX;
    mScaleY = tY;
}

void Sprite::Scale(float tFactorX, float tFactorY) {
    mScaleX *= tFactorX;
    mScaleY *= tFactorY;
}

void Sprite::SetRotation(int tAngle) {
    mAngle = tAngle;
}

void Sprite::Rotate(int tAngle) {
    mAngle += tAngle;
}

void Sprite::SetFlip(FLIP tFlip) {
    mFlip = tFlip;
}

void Sprite::SetTextureColor(Uint8 tRed, Uint8 tGreen, Uint8 tBlue) {
    mTexture.SetColor(tRed, tGreen, tBlue);
}

void Sprite::Render(SDL_Renderer* tRenderer) {
    mTexture.Render(tRenderer, mPosX, mPosY, &mTextureRect, mAngle, mScaleX, mScaleY, nullptr,
                    SDL_RendererFlip(mFlip));
}
