//
// Created by mac on 2024/5/11.
//

#include "game/Object.h"
#include "game/ComponentSprite.h"

ComponentSprite::ComponentSprite(Object* owner):
    Component(owner), textureID(-1), allocator(nullptr) {}


void ComponentSprite::SetTextureAllocator(ResourceAllocator<LTexture>* a){
    this->allocator = a;
}

Sprite& ComponentSprite::GetSprite() {
    return sprite;
}

std::shared_ptr<LTexture> ComponentSprite::GetTexture() {
    return allocator->Get(textureID);
}

void ComponentSprite::Load(int id) {
    if(id >= 0){
        std::shared_ptr<LTexture> texture = allocator->Get(id);
        sprite.setTexture(*texture, true);
    }
}

void ComponentSprite::Load(const std::string &filePath) {
    if(allocator){
        int id = allocator->Add(filePath);

        if(id >= 0){
            Load(id);
            textureID = id;
        }
    }
}

void ComponentSprite::RenderUpdate() {
    sprite.render();
}

void ComponentSprite::LateUpdate(float deltaTime) {
    int newPosX = owner->transform->GetPositionX();
    int newPosY =owner->transform->GetPositionY();
    sprite.setPosition(newPosX, newPosY);
}
