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

void ComponentSprite::Scale(float tFactorX, float tFactorY) {
    mSprite.Scale(tFactorX, tFactorY);
}

void ComponentSprite::SetFlip(FLIP tFlip) {
    mSprite.SetFlip(tFlip);
}

void ComponentSprite::SetRotation(int tAngle) {
    mSprite.SetRotation(tAngle);
}

void ComponentSprite::SetTextureColor(Uint8 tRed, Uint8 tGreen, Uint8 tBlue) {
    mSprite.SetTextureColor(tRed, tGreen, tBlue);
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
        mSprite.SetTexture(*texture);
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
