//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTTRANSFORM_H
#define MAIN_COMPONENTTRANSFORM_H

#include "game/component.h"

class ComponentTransform : public Component {
   public:
    explicit ComponentTransform(Object* tOwner);

    void SetPosition(int tX, int tY);

    void AddPosition(int tX, int tY);

    void SetX(int tX);
    void SetY(int tY);

    [[nodiscard]] auto GetPositionX() const -> int;
    [[nodiscard]] auto GetPositionY() const -> int;

   private:
    int mPosX;
    int mPosY;
};

#endif  // MAIN_COMPONENTTRANSFORM_H
