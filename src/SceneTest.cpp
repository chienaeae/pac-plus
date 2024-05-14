//
// Created by mac on 2024/5/11.
//

#include "game/Object.h"
#include "game/ComponentSprite.h"
#include "game/ComponentKeyboardMovement.h"
#include "SceneTest.h"

SceneTest::SceneTest(SceneStateMachine &sceneStateMachine,
                     ResourceAllocator<LTexture>& textureAllocator)
                     : sceneStateMachine(sceneStateMachine),
                       textureAllocator(textureAllocator) {}

void SceneTest::OnCreate() {
    std::shared_ptr<Object> square = std::make_shared<Object>();

    auto sprite = square->AddComponent<ComponentSprite>();
    sprite->SetTextureAllocator(&textureAllocator);
    sprite->Load("assets/square.png");
    sprite->GetSprite().setScale(5.0f, 5.0f);
    sprite->GetTexture()->SetColor(0, 140, 255);

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

void SceneTest::Update(float deltaTime)  {
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
