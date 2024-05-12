//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTSPRITE_H
#define MAIN_COMPONENTSPRITE_H

#include <string>

#include "game/LTexture.h"
#include "game/Sprite.h"
#include "game/ResourceAllocator.h"
#include "game/Component.h"

class ComponentSprite: public Component {
public:
    ComponentSprite(Object* owner);

    Sprite& GetSprite();

    std::shared_ptr<LTexture> GetTexture();

    void Load(const std::string& filePath);

    void RenderUpdate() override;

    void LateUpdate(float deltaTime) override;

    void Load(int id);

    void SetTextureAllocator(ResourceAllocator<LTexture>* a);

private:
    ResourceAllocator<LTexture> * allocator;
    int textureID;
    Sprite sprite;
};

#endif //MAIN_COMPONENTSPRITE_H
