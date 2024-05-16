//
// Created by mac on 2024/5/12.
//

#include "game/object-collection.h"

#include <SDL_events.h>

#include <memory>

#include "game/object.h"

void ObjectCollection::Update(float tDeltaTime) {
    for (auto& o : mObjects) {
        o->Update(tDeltaTime);
    }
}

void ObjectCollection::LateUpdate(float tDeltaTime) {
    for (auto& o : mObjects) {
        o->LateUpdate(tDeltaTime);
    }
}

void ObjectCollection::EventUpdate(SDL_Event* tEvent) {
    for (auto& o : mObjects) {
        o->EventUpdate(tEvent);
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

void ObjectCollection::Add(const std::shared_ptr<Object>& tObject) {
    mNewObjects.push_back(tObject);
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
