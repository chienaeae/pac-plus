//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTSPRITE_H
#define MAIN_COMPONENTSPRITE_H

#include <string>

#include "game/component.h"
#include "game/object.h"
#include "game/resource-allocator.h"
#include "game/sprite.h"
#include "game/texture.h"

class ComponentSprite : public Component {
   public:
    explicit ComponentSprite(Object* tOwner);

    auto GetSprite() -> Sprite&;

    auto GetTexture() -> std::shared_ptr<Texture>;

    void SetTextureRect(int x, int y, int width, int height);

    void SetTextureRect(const SDL_Rect& rect);

    void Load(const std::string& tFilePath);

    void RenderUpdate(SDL_Renderer* tRenderer) override;

    void LateUpdate(float tDeltaTime) override;

    void Load(int tID);

    void SetTextureAllocator(ResourceAllocator<Texture>* tAllocator);

   private:
    ResourceAllocator<Texture>* mAllocator;
    int mTextureID;
    Sprite mSprite;
};

#endif  // MAIN_COMPONENTSPRITE_H
