//
// Created by mac on 2024/5/10.
//
#include <SDL_events.h>
#include <game/SceneStateMachine.h>

#include <memory>
#include <utility>

#include "game/Scene.h"

SceneStateMachine::SceneStateMachine() : currentScene(nullptr), insertedSceneID() {}

void SceneStateMachine::EventUpdate(SDL_Event* e) {
    if (currentScene) {
        currentScene->EventUpdate(e);
    }
}

void SceneStateMachine::Update(float deltaTime) {
    if (currentScene) {
        currentScene->Update(deltaTime);
    }
}

void SceneStateMachine::LateUpdate(float deltaTime) {
    if (currentScene) {
        currentScene->LateUpdate(deltaTime);
    }
}

void SceneStateMachine::RenderUpdate() {
    if (currentScene) {
        currentScene->RenderUpdate();
    }
}

auto SceneStateMachine::Add(const std::shared_ptr<Scene>& scene) -> unsigned int {
    auto inserted = scenes.insert(std::make_pair(insertedSceneID, scene));

    insertedSceneID++;

    inserted.first->second->OnCreate();

    return insertedSceneID - 1;
}

void SceneStateMachine::Remove(unsigned int id) {
    auto it = scenes.find(id);
    if (it != scenes.end()) {
        if (currentScene == it->second) {
            currentScene = nullptr;
        }

        it->second->OnDestroy();

        scenes.erase(it);
    }
}

void SceneStateMachine::SwitchTo(unsigned int id) {
    auto it = scenes.find(id);
    if (it != scenes.end()) {
        if (currentScene) {
            // If we have a current scene, we call its OnDeactivate method.
            currentScene->OnDeactivate();
        }

        // Setting the current scene ensures that it is updated and drawn.
        currentScene = it->second;

        currentScene->OnActivate();
    }
}
