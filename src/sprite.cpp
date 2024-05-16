//
// Created by mac on 2024/5/11.
//

#include "game/sprite.h"

#include "game/texture.h"

Sprite::Sprite() : mPosX(0), mPosY(0), mAngle(0), mTextureRect(), mScaleX(1.0f), mScaleY(1.0f) {}

auto Sprite::getTextureRect() const -> const SDL_Rect& {
    return mTextureRect;
}

auto Sprite::getTexture() const -> const Texture* {
    return &mTexture;
}

auto Sprite::getPositionX() const -> int {
    return mPosX;
}

auto Sprite::getPositionY() const -> int {
    return mPosY;
}

auto Sprite::getScaleX() const -> float {
    return mScaleX;
}

auto Sprite::getScaleY() const -> float {
    return mScaleY;
}

auto Sprite::getRotation() const -> int {
    return mAngle;
}

void Sprite::setTextureRect(const SDL_Rect& tTextureRect) {
    mTextureRect = tTextureRect;
}

void Sprite::setTexture(const Texture& tTexture, bool tResetRect) {
    if (tResetRect) {
        setTextureRect(SDL_Rect{0, 0, tTexture.GetWidth(), tTexture.GetHeight()});
    }
    mTexture = tTexture;
}

void Sprite::setPosition(int tX, int tY) {
    mPosX = tX;
    mPosY = tY;
}

void Sprite::move(int tOffsetX, int tOffsetY) {
    mPosX += tOffsetX;
    mPosY += tOffsetY;
}

void Sprite::setScale(float tX, float tY) {
    mScaleX = tX;
    mScaleY = tY;
}

void Sprite::scale(float tFactorX, float tFactorY) {
    mScaleX *= tFactorX;
    mScaleY *= tFactorY;
}

void Sprite::setRotation(int tAngle) {
    mAngle = tAngle;
}

void Sprite::rotate(int tAngle) {
    mAngle += tAngle;
}

void Sprite::render() {
    mTexture.Render(mPosX, mPosY, &mTextureRect, mAngle, mScaleX, mScaleY);
}
