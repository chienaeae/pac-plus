//
// Created by mac on 2024/5/11.
//

#include "game/object.h"

#include <SDL_events.h>

#include "game/component-transform.h"

Object::Object() : mQueuedForRemoval(false) {
    Transform = AddComponent<ComponentTransform>();
}

void Object::Awake() {
    for (int i = static_cast<int>(mComponents.size()) - 1; i >= 0; i--) {
        mComponents[i]->Awake();
    }
}

void Object::Start() {
    for (int i = static_cast<int>(mComponents.size()) - 1; i >= 0; i--) {
        mComponents[i]->Start();
    }
}

void Object::Update(float tDeltaTime) {
    for (int i = static_cast<int>(mComponents.size()) - 1; i >= 0; i--) {
        mComponents[i]->Update(tDeltaTime);
    }
}

void Object::LateUpdate(float tDeltaTime) {
    for (int i = static_cast<int>(mComponents.size()) - 1; i >= 0; i--) {
        mComponents[i]->LateUpdate(tDeltaTime);
    }
}

void Object::EventUpdate(SDL_Event *tEvent) {
    for (int i = static_cast<int>(mComponents.size()) - 1; i >= 0; i--) {
        mComponents[i]->EventUpdate(tEvent);
    }
}

void Object::RenderUpdate() {
    for (int i = static_cast<int>(mComponents.size()) - 1; i >= 0; i--) {
        mComponents[i]->RenderUpdate();
    }
}

void Object::QueueForRemoval() {
    mQueuedForRemoval = true;
}

auto Object::IsQueuedForRemoval() const -> bool {
    return mQueuedForRemoval;
}
