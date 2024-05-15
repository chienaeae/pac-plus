//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENTKEYBOARDMOVEMENT_H
#define MAIN_COMPONENTKEYBOARDMOVEMENT_H

#include <SDL.h>

#include "game/component.h"
#include "game/object.h"

class ComponentKeyboardMovement : public Component {
   public:
    explicit ComponentKeyboardMovement(Object *tOwner);

    void SetSpeed(int tSpeed);

    void Update(float tDeltaTime) override;

    void EventUpdate(SDL_Event *tEvent) override;

   private:
    int mMoveSpeed;
    int mVelX;
    int mVelY;
};

#endif  // MAIN_COMPONENTKEYBOARDMOVEMENT_H
