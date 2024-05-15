//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTSPRITE_H
#define MAIN_COMPONENTSPRITE_H

#include <string>

#include "game/Component.h"
#include "game/LTexture.h"
#include "game/ResourceAllocator.h"
#include "game/Sprite.h"

class ComponentSprite : public Component {
   public:
    explicit ComponentSprite(Object* tOwner);

    Sprite& GetSprite();

    std::shared_ptr<LTexture> GetTexture();

    void Load(const std::string& tFilePath);

    void RenderUpdate() override;

    void LateUpdate(float tDeltaTime) override;

    void Load(int tID);

    void SetTextureAllocator(ResourceAllocator<LTexture>* tAllocator);

   private:
    ResourceAllocator<LTexture>* mAllocator;
    int mTextureID;
    Sprite mSprite;
};

#endif  // MAIN_COMPONENTSPRITE_H
