//
// Created by mac on 2024/5/10.
//
#include <SDL_events.h>
#include <game/SceneStateMachine.h>

#include <memory>
#include <utility>

#include "game/Scene.h"

SceneStateMachine::SceneStateMachine() : mCurrentScene(nullptr), mInsertedSceneID() {}

void SceneStateMachine::EventUpdate(SDL_Event* tEvent) {
    if (mCurrentScene) {
        mCurrentScene->EventUpdate(tEvent);
    }
}

void SceneStateMachine::Update(float tDeltaTime) {
    if (mCurrentScene) {
        mCurrentScene->Update(tDeltaTime);
    }
}

void SceneStateMachine::LateUpdate(float tDeltaTime) {
    if (mCurrentScene) {
        mCurrentScene->LateUpdate(tDeltaTime);
    }
}

void SceneStateMachine::RenderUpdate() {
    if (mCurrentScene) {
        mCurrentScene->RenderUpdate();
    }
}

auto SceneStateMachine::Add(const std::shared_ptr<Scene>& tScene) -> unsigned int {
    auto inserted = mScenes.insert(std::make_pair(mInsertedSceneID, tScene));

    mInsertedSceneID++;

    inserted.first->second->OnCreate();

    return mInsertedSceneID - 1;
}

void SceneStateMachine::Remove(unsigned int tID) {
    auto it = mScenes.find(tID);
    if (it != mScenes.end()) {
        if (mCurrentScene == it->second) {
            mCurrentScene = nullptr;
        }

        it->second->OnDestroy();

        mScenes.erase(it);
    }
}

void SceneStateMachine::SwitchTo(unsigned int tID) {
    auto it = mScenes.find(tID);
    if (it != mScenes.end()) {
        if (mCurrentScene) {
            // If we have a current scene, we call its OnDeactivate method.
            mCurrentScene->OnDeactivate();
        }

        // Setting the current scene ensures that it is updated and drawn.
        mCurrentScene = it->second;

        mCurrentScene->OnActivate();
    }
}
