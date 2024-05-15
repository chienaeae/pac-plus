//
// Created by mac on 2024/5/12.
//

#include "game/ObjectCollection.h"

#include <SDL_events.h>

#include <memory>

#include "game/Object.h"

void ObjectCollection::Update(float deltaTime) {
    for (auto& o : mObjects) {
        o->Update(deltaTime);
    }
}

void ObjectCollection::LateUpdate(float deltaTime) {
    for (auto& o : mObjects) {
        o->LateUpdate(deltaTime);
    }
}

void ObjectCollection::EventUpdate(SDL_Event* e) {
    for (auto& o : mObjects) {
        o->EventUpdate(e);
    }
}

void ObjectCollection::RenderUpdate() {
    for (auto& o : mObjects) {
        o->RenderUpdate();
    }
}

auto ObjectCollection::Size() -> int {
    return static_cast<int>(mObjects.size());
}

void ObjectCollection::Clear() {
    mObjects.clear();

    if (!mNewObjects.empty()) {
        mNewObjects.clear();
    }
}

void ObjectCollection::Add(const std::shared_ptr<Object>& object) {
    mNewObjects.push_back(object);
}

void ObjectCollection::ProcessNewObjects() {
    if (!mNewObjects.empty()) {
        for (const auto& o : mNewObjects) {
            o->Awake();
        }

        for (const auto& o : mNewObjects) {
            o->Start();
        }

        mObjects.assign(mNewObjects.begin(), mNewObjects.end());

        mNewObjects.clear();
    }
}

void ObjectCollection::ProcessRemovals() {
    auto objIterator = mObjects.begin();
    while (objIterator != mObjects.end()) {
        auto obj = **objIterator;

        if (obj.IsQueuedForRemoval()) {
            objIterator = mObjects.erase(objIterator);
        } else {
            objIterator++;
        }
    }
}
