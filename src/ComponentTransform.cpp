//
// Created by mac on 2024/5/11.
//

#include "game/ComponentTransform.h"

#include "game/Component.h"

ComponentTransform::ComponentTransform(Object *tOwner) : Component(tOwner), mPosX(0), mPosY(0) {}

void ComponentTransform::SetPosition(int tX, int tY) {
    mPosX = tX;
    mPosY = tY;
}

void ComponentTransform::AddPosition(int tX, int tY) {
    mPosX += tX;
    mPosY += tY;
}

void ComponentTransform::SetX(int tX) {
    mPosX = tX;
}

void ComponentTransform::SetY(int tY) {
    mPosY = tY;
}

auto ComponentTransform::GetPositionX() const -> int {
    return mPosX;
}

auto ComponentTransform::GetPositionY() const -> int {
    return mPosY;
}
