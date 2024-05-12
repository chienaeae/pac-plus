//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTTRANSFORM_H
#define MAIN_COMPONENTTRANSFORM_H

#include "Component.h"

class ComponentTransform: public Component {
public:
    ComponentTransform(Object* owner);

    void SetPosition(int x, int y);

    void AddPosition(int x, int y);

    void SetX(int x);
    void SetY(int y);

    const int GetPositionX() const;
    const int GetPositionY() const;

private:
    int posX;
    int posY;
};

#endif //MAIN_COMPONENTTRANSFORM_H
