//
// Created by mac on 5/15/24.
//

#include "pac-plus.h"

#include <iostream>

#include "scene-test.h"

void PacPlus::OnCreate() {
    std::shared_ptr<SceneTest> const testScene =
        std::make_shared<SceneTest>(mSceneStateMachine, mTextureAllocator);

    unsigned int const testSceneID = mSceneStateMachine.Add(testScene);

    mSceneStateMachine.SwitchTo(testSceneID);
};

void PacPlus::Update(float tDeltaTime) {
    mSceneStateMachine.Update(tDeltaTime);
};

void PacPlus::LateUpdate(float tDeltaTime) {
    mSceneStateMachine.LateUpdate(tDeltaTime);
};

void PacPlus::RenderUpdate(SDL_Renderer* tRenderer) {
    mSceneStateMachine.RenderUpdate(tRenderer);
};

void PacPlus::EventUpdate(SDL_Event* tEvent) {
    mSceneStateMachine.EventUpdate(tEvent);
};
