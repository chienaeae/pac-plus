//
// Created by mac on 2024/5/11.
//

#include "game/Object.h"
#include "game/ComponentSprite.h"
#include "game/ComponentKeyboardMovement.h"
#include "SceneTest.h"

SceneTest::SceneTest(SceneStateMachine &sceneStateMachine) : sceneStateMachine(sceneStateMachine) {}

void SceneTest::OnCreate() {
    square = std::make_shared<Object>();

    auto sprite = square->AddComponent<ComponentSprite>();
    sprite->Load("assets/square.png");
    sprite->GetSprite().setScale(5.0f, 5.0f);
    sprite->GetTexture().setColor(0, 140, 255);
    auto movement = square->AddComponent<ComponentKeyboardMovement>();
}

void SceneTest::OnActivate() {
    currentSeconds = 0.f;
}

void SceneTest::OnDestroy() {}

void SceneTest::SetSwitchToScene(unsigned int id) {
    switchToState = id;
}

void SceneTest::Update(float deltaTime)  {
    currentSeconds += deltaTime;
    square->Update(deltaTime);
}

void SceneTest::LateUpdate(float deltaTime) {
    square->LateUpdate(deltaTime);
}


void SceneTest::EventUpdate(SDL_Event *e) {
    square->EventUpdate(e);
}

void SceneTest::RenderUpdate() {
    square->RenderUpdate();
}
