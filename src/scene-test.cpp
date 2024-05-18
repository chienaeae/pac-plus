//
// Created by mac on 2024/5/11.
//

#include "scene-test.h"

#include <SDL_events.h>

#include <iostream>
#include <memory>

#include "game/component-keyboard-movement.h"
#include "game/component-sprite.h"
#include "game/object.h"
#include "game/resource-allocator.h"
#include "game/scene-state-machine.h"
#include "game/texture.h"

SceneTest::SceneTest(SceneStateMachine &tSceneStateMachine,
                     ResourceAllocator<Texture> &tTextureAllocator)
    : mSceneStateMachine(tSceneStateMachine), mTextureAllocator(tTextureAllocator) {}

void SceneTest::OnCreate() {
    std::shared_ptr<Object> const square = std::make_shared<Object>();

    auto sprite = square->AddComponent<ComponentSprite>();
    sprite->SetTextureAllocator(&mTextureAllocator);
    sprite->Load("assets/square.png");

    const float SCALE_X = 5.0f;
    const float SCALE_Y = 5.0f;
    sprite->GetSprite().setScale(SCALE_X, SCALE_Y);

    const int COLOR_R = 0;
    const int COLOR_G = 140;
    const int COLOR_B = 255;
    sprite->GetTexture()->SetColor(COLOR_R, COLOR_G, COLOR_B);

    auto movement = square->AddComponent<ComponentKeyboardMovement>();

    mObjects.Add(square);
}

void SceneTest::OnActivate() {
    currentSeconds = 0.f;
}

void SceneTest::OnDestroy() {}

void SceneTest::SetSwitchToScene(unsigned int tID) {
    switchToState = tID;
}

void SceneTest::Update(float tDeltaTime) {
    currentSeconds += tDeltaTime;
    mObjects.ProcessRemovals();
    mObjects.ProcessNewObjects();
    mObjects.Update(tDeltaTime);
}

void SceneTest::LateUpdate(float deltaTime) {
    mObjects.LateUpdate(deltaTime);
}

void SceneTest::EventUpdate(SDL_Event *e) {
    mObjects.EventUpdate(e);
}

void SceneTest::RenderUpdate(SDL_Renderer *tRenderer) {
    mObjects.RenderUpdate(tRenderer);
}
