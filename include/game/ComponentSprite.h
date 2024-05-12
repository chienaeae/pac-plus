//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTSPRITE_H
#define MAIN_COMPONENTSPRITE_H

#include <string>

#include "game/LTexture.h"
#include "game/Sprite.h"
#include "Component.h"

class ComponentSprite: public Component {
public:
    ComponentSprite(Object* owner);

    Sprite& GetSprite();

    LTexture& GetTexture();

    void Load(const std::string& filePath);

    void RenderUpdate() override;

    void LateUpdate(float deltaTime) override;

private:
    LTexture texture;
    Sprite sprite;
};

#endif //MAIN_COMPONENTSPRITE_H
