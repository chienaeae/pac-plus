//
// Created by mac on 2024/5/11.
//

#include "game/ComponentTransform.h"

#include "game/Component.h"

ComponentTransform::ComponentTransform(Object *owner) : Component(owner), posX(0), posY(0) {}

void ComponentTransform::SetPosition(int x, int y) {
    posX = x;
    posY = y;
}

void ComponentTransform::AddPosition(int x, int y) {
    posX += x;
    posY += y;
}

void ComponentTransform::SetX(int x) {
    posX = x;
}

void ComponentTransform::SetY(int y) {
    posY = y;
}

auto ComponentTransform::GetPositionX() const -> int {
    return posX;
}

auto ComponentTransform::GetPositionY() const -> int {
    return posY;
}
