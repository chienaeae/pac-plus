//
// Created by mac on 2024/5/11.
//

#include "SceneTest.h"

SceneTest::SceneTest(SceneStateMachine &sceneStateMachine) : sceneStateMachine(sceneStateMachine) {}

void SceneTest::OnCreate() {

}

void SceneTest::OnActivate() {
    currentSeconds = 0.f;
}

void SceneTest::OnDestroy() {}

void SceneTest::SetSwitchToScene(unsigned int id) {
    switchToState = id;
}

void SceneTest::Update() {
//    currentSeconds += deltaTime;
}

void SceneTest::RenderUpdate() {

}
