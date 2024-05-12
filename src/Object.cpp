//
// Created by mac on 2024/5/11.
//

#include "game/Object.h"

Object::Object() {
    transform = AddComponent<ComponentTransform>();
}

void Object::Awake() {
    for(int i = components.size() - 1; i >= 0; i--){
        components[i]->Awake();
    }
}

void Object::Start() {
    for(int i = components.size() - 1; i >= 0; i--){
        components[i]->Start();
    }
}

void Object::Update(float deltaTime) {
    for(int i = components.size() - 1; i >= 0; i--){
        components[i]->Update(deltaTime);
    }
}

void Object::LateUpdate(float deltaTime) {
    for(int i = components.size() - 1; i >= 0; i--){
        components[i]->LateUpdate(deltaTime);
    }
}

void Object::EventUpdate(SDL_Event *e) {
    for(int i = components.size() - 1; i >= 0; i--){
        components[i]->EventUpdate(e);
    }
}

void Object::RenderUpdate()  {
    for(int i = components.size() - 1; i >= 0; i--){
        components[i]->RenderUpdate();
    }
}
