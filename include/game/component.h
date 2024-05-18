//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include "SDL.h"

/* As our Object requires a reference to Component and Component
requires a reference to Object; we forward declare Object */
class Object;

class Component {
   public:
    explicit Component(Object *tOwner) : mOwner(tOwner) {};

    virtual void Awake() {};

    virtual void Start() {};

    virtual void Update(float tDeltaTime) {};

    virtual void LateUpdate(float tDeltaTime) {};

    virtual void RenderUpdate(SDL_Renderer *tRenderer) {};

    virtual void EventUpdate(SDL_Event *tEvent) {};

   protected:
    Object *mOwner;
};

#endif  // MAIN_COMPONENT_H
