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
    SceneTest(SceneStateMachine& tSceneStateMachine,
              ResourceAllocator<LTexture>& tTextureAllocator);

    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;

    void Update(float tDeltaTime) override;
    void LateUpdate(float tDeltaTime) override;
    void EventUpdate(SDL_Event* tEvent) override;
    void RenderUpdate() override;

    void SetSwitchToScene(unsigned int tID);

   private:
    SceneStateMachine& mSceneStateMachine;

    ResourceAllocator<LTexture>& mTextureAllocator;

    ObjectCollection mObjects;
    // How long the scene has currently been visible
    float currentSeconds{};

    unsigned int switchToState{};
};

#endif  // MAIN_SCENETEST_H
