//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_SCENETEST_H
#define MAIN_SCENETEST_H

#include "game/object-collection.h"
#include "game/object.h"
#include "game/resource-allocator.h"
#include "game/scene-state-machine.h"
#include "game/scene.h"
#include "square.h"

class SceneTest : public Scene {
   public:
    SceneTest(SceneStateMachine& tSceneStateMachine, ResourceAllocator<Texture>& tTextureAllocator);

    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;

    void Update(float tDeltaTime) override;
    void LateUpdate(float tDeltaTime) override;
    void EventUpdate(SDL_Event* tEvent) override;
    void RenderUpdate(SDL_Renderer* tRenderer) override;

    void SetSwitchToScene(unsigned int tID);

   private:
    SceneStateMachine& mSceneStateMachine;

    ResourceAllocator<Texture>& mTextureAllocator;

    ObjectCollection mObjects;
    // How long the scene has currently been visible
    float currentSeconds{};

    unsigned int switchToState{};
};

#endif  // MAIN_SCENETEST_H
