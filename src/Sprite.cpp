//
// Created by mac on 2024/5/11.
//

#include "game/Sprite.h"

Sprite::Sprite():posX(0), posY(0), angle(0), textureRect(), scaleX(1.0f), scaleY(1.0f) {}

const SDL_Rect& Sprite::getTextureRect() const {
    return textureRect;
}

const LTexture* Sprite::getTexture() const {
    return &texture;
}

const int Sprite::getPositionX() const{
    return posX;
}

const int Sprite::getPositionY() const{
    return posY;
}

const float Sprite::getScaleX() const{
    return scaleX;
}

const float Sprite::getScaleY() const{
    return scaleY;
}

const int Sprite::getRotation() const{
    return angle;
}

void Sprite::setTextureRect(const SDL_Rect &tr){
    textureRect = tr;
}

void Sprite::setTexture(const LTexture &t, bool resetRect){
    if(resetRect){
        setTextureRect(SDL_Rect {0, 0, t.getWidth(), t.getHeight()});
    }
    texture = t;
}

void Sprite::setPosition(int x, int y){
    posX = x;
    posY = y;
}

void Sprite::move(int offsetX, int offsetY){
    posX += offsetX;
    posY += offsetY;
}

void Sprite::setScale(float x, float y){
    scaleX = x;
    scaleY = y;
}

void Sprite::scale(float factorX, float factorY){
    scaleX *= factorX;
    scaleY *= factorY;
}

void Sprite::setRotation(int a){
    angle = a;
}

void Sprite::rotate(int a){
    angle += a;
}

void Sprite::render(){
    texture.render(posX, posY, &textureRect, angle, scaleX, scaleY);
}
