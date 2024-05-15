//
// Created by mac on 2024/5/11.
//

#include "game/Sprite.h"

#include "game/LTexture.h"

Sprite::Sprite() : posX(0), posY(0), angle(0), textureRect(), scaleX(1.0f), scaleY(1.0f) {}

auto Sprite::getTextureRect() const -> const SDL_Rect& {
    return textureRect;
}

auto Sprite::getTexture() const -> const LTexture* {
    return &texture;
}

auto Sprite::getPositionX() const -> int {
    return posX;
}

auto Sprite::getPositionY() const -> int {
    return posY;
}

auto Sprite::getScaleX() const -> float {
    return scaleX;
}

auto Sprite::getScaleY() const -> float {
    return scaleY;
}

auto Sprite::getRotation() const -> int {
    return angle;
}

void Sprite::setTextureRect(const SDL_Rect& tr) {
    textureRect = tr;
}

void Sprite::setTexture(const LTexture& t, bool resetRect) {
    if (resetRect) {
        setTextureRect(SDL_Rect{0, 0, t.GetWidth(), t.GetHeight()});
    }
    texture = t;
}

void Sprite::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

void Sprite::move(int offsetX, int offsetY) {
    posX += offsetX;
    posY += offsetY;
}

void Sprite::setScale(float x, float y) {
    scaleX = x;
    scaleY = y;
}

void Sprite::scale(float factorX, float factorY) {
    scaleX *= factorX;
    scaleY *= factorY;
}

void Sprite::setRotation(int a) {
    angle = a;
}

void Sprite::rotate(int a) {
    angle += a;
}

void Sprite::render() {
    texture.Render(posX, posY, &textureRect, angle, scaleX, scaleY);
}
