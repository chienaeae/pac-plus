//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTKEYBOARDMOVEMENT_H
#define MAIN_COMPONENTKEYBOARDMOVEMENT_H

#include <SDL.h>


#include "game/Component.h"

class ComponentKeyboardMovement: public Component {
public:
    ComponentKeyboardMovement(Object *owner);

    void SetSpeed(int speed);

    void Update(float deltaTime) override;

    void EventUpdate(SDL_Event * e) override;

private :
    int moveSpeed;
    int velX;
    int velY;
};

#endif //MAIN_COMPONENTKEYBOARDMOVEMENT_H
