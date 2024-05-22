//
// Created by mac on 2024/5/11.
//

#include "scene-test.h"

#include <SDL_events.h>

#include <iostream>
#include <memory>

#include "game/component-animation.h"
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
    std::shared_ptr<Object> const player = std::make_shared<Object>();

    auto sprite = player->AddComponent<ComponentSprite>();
    sprite->SetTextureAllocator(&mTextureAllocator);
    int actorTextureID = mTextureAllocator.Add("assets/example.png");

    auto animation = player->AddComponent<ComponentAnimation>();
    const int frameWidth = 32;
    const int frameHeight = 32;
    const float frameSeconds = 0.05f;

    // idle
    std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>(FacingDirection::Right);
    idleAnimation->AddFrame(actorTextureID, 0, 0, frameWidth, frameHeight, frameSeconds);

    // walk
    std::shared_ptr<Animation> walkAnimation = std::make_shared<Animation>(FacingDirection::Right);
    walkAnimation->AddFrame(actorTextureID, 0, 0, frameWidth, frameHeight, frameSeconds);
    walkAnimation->AddFrame(actorTextureID, frameWidth * 1, 0, frameWidth, frameHeight,
                            frameSeconds);
    walkAnimation->AddFrame(actorTextureID, frameWidth * 2, 0, frameWidth, frameHeight,
                            frameSeconds);

    animation->AddAnimation(AnimationState::Idle, idleAnimation);
    animation->AddAnimation(AnimationState::Walk, walkAnimation);

    auto movement = player->AddComponent<ComponentKeyboardMovement>();

    mObjects.Add(player);
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
