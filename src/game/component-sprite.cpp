//
// Created by mac on 2024/5/11.
//

#include "game/component-sprite.h"

#include <memory>
#include <string>

#include "game/component.h"
#include "game/object.h"
#include "game/resource-allocator.h"
#include "game/sprite.h"
#include "game/texture.h"

ComponentSprite::ComponentSprite(Object *tOwner)
    : Component(tOwner), mTextureID(-1), mAllocator(nullptr), mSprite() {}

void ComponentSprite::SetTextureAllocator(ResourceAllocator<Texture> *tAllocator) {
    mAllocator = tAllocator;
}

auto ComponentSprite::GetSprite() -> Sprite & {
    return mSprite;
}

auto ComponentSprite::GetTexture() -> std::shared_ptr<Texture> {
    return mAllocator->Get(mTextureID);
}

void ComponentSprite::SetTextureRect(int x, int y, int width, int height) {
    mSprite.SetTextureRect(SDL_Rect{x, y, width, height});
}

void ComponentSprite::SetTextureRect(const SDL_Rect &rect) {
    mSprite.SetTextureRect(rect);
}

void ComponentSprite::Load(int tID) {
    if (tID >= 0 && tID != mTextureID) {
        mTextureID = tID;
        std::shared_ptr<Texture> const texture = mAllocator->Get(tID);
        mSprite.SetTexture(*texture, true);
    }
}

void ComponentSprite::Load(const std::string &tFilePath) {
    if (mAllocator) {
        int const id = mAllocator->Add(tFilePath);

        if (id >= 0) {
            Load(id);
        }
    }
}

void ComponentSprite::RenderUpdate(SDL_Renderer *tRenderer) {
    mSprite.Render(tRenderer);
}

void ComponentSprite::LateUpdate(float /*deltaTime*/) {
    int const newPosX = mOwner->Transform->GetPositionX();
    int const newPosY = mOwner->Transform->GetPositionY();
    mSprite.SetPosition(newPosX, newPosY);
}
