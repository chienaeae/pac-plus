//
// Created by mac on 2024/5/11.
//

#include "SceneTest.h"

#include <SDL_events.h>

#include <memory>

#include "game/ComponentKeyboardMovement.h"
#include "game/ComponentSprite.h"
#include "game/LTexture.h"
#include "game/Object.h"
#include "game/ResourceAllocator.h"
#include "game/SceneStateMachine.h"

SceneTest::SceneTest(SceneStateMachine &sceneStateMachine,
                     ResourceAllocator<LTexture> &textureAllocator)
    : sceneStateMachine(sceneStateMachine), textureAllocator(textureAllocator) {}

void SceneTest::OnCreate() {
    std::shared_ptr<Object> const square = std::make_shared<Object>();

    auto sprite = square->AddComponent<ComponentSprite>();
    sprite->SetTextureAllocator(&textureAllocator);
    sprite->Load("assets/square.png");

    const float SCALE_X = 5.0f;
    const float SCALE_Y = 5.0f;
    sprite->GetSprite().setScale(SCALE_X, SCALE_Y);

    const int COLOR_R = 0;
    const int COLOR_G = 140;
    const int COLOR_B = 255;
    sprite->GetTexture()->SetColor(COLOR_R, COLOR_G, COLOR_B);

    auto movement = square->AddComponent<ComponentKeyboardMovement>();

    objects.Add(square);
}

void SceneTest::OnActivate() {
    currentSeconds = 0.f;
}

void SceneTest::OnDestroy() {}

void SceneTest::SetSwitchToScene(unsigned int id) {
    switchToState = id;
}

void SceneTest::Update(float deltaTime) {
    currentSeconds += deltaTime;
    objects.ProcessRemovals();
    objects.ProcessNewObjects();
    objects.Update(deltaTime);
}

void SceneTest::LateUpdate(float deltaTime) {
    objects.LateUpdate(deltaTime);
}

void SceneTest::EventUpdate(SDL_Event *e) {
    objects.EventUpdate(e);
}

void SceneTest::RenderUpdate() {
    objects.RenderUpdate();
}
