//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_SCENETEST_H
#define MAIN_SCENETEST_H

#include "Square.h"
#include "game/Object.h"
#include "game/ObjectCollection.h"
#include "game/ResourceAllocator.h"
#include "game/Scene.h"
#include "game/SceneStateMachine.h"

class SceneTest : public Scene {
   public:
    SceneTest(SceneStateMachine& sceneStateMachine, ResourceAllocator<LTexture>& textureAllocator);

    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;

    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void EventUpdate(SDL_Event* e) override;
    void RenderUpdate() override;

    void SetSwitchToScene(unsigned int id);

   private:
    SceneStateMachine& sceneStateMachine;

    ResourceAllocator<LTexture>& textureAllocator;

    ObjectCollection objects;
    // How long the scene has currently been visible
    float currentSeconds{};

    unsigned int switchToState{};
};

#endif  // MAIN_SCENETEST_H
