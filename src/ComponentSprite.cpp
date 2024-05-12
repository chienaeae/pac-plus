//
// Created by mac on 2024/5/11.
//

#include "game/Object.h"
#include "game/ComponentSprite.h"

ComponentSprite::ComponentSprite(Object* owner): Component(owner) {}

Sprite& ComponentSprite::GetSprite() {
    return sprite;
}

LTexture& ComponentSprite::GetTexture() {
    return texture;
}

void ComponentSprite::Load(const std::string &filePath) {
    texture.loadFromFile(filePath);
    sprite.setTexture(texture, true);
}

void ComponentSprite::RenderUpdate() {
    sprite.render();
}

void ComponentSprite::LateUpdate(float deltaTime) {
    int newPosX = owner->transform->GetPositionX();
    int newPosY =owner->transform->GetPositionY();
    sprite.setPosition(newPosX, newPosY);
}
