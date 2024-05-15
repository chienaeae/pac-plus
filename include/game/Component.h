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
    explicit Component(Object *owner) : owner(owner) {};

    virtual void Awake() {};

    virtual void Start() {};

    virtual void Update(float deltaTime) {};

    virtual void LateUpdate(float deltaTime) {};

    virtual void RenderUpdate() {};

    virtual void EventUpdate(SDL_Event *e) {};

   protected:
    Object *owner;
};

#endif  // MAIN_COMPONENT_H
