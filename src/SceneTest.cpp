//
// Created by mac on 2024/5/11.
//

#include "SceneTest.h"

SceneTest::SceneTest(SceneStateMachine &sceneStateMachine) : sceneStateMachine(sceneStateMachine) {}

void SceneTest::OnCreate() {
    // Init assets
    squareTexture.loadFromFile("assets/square.png");
    squareTexture.setColor(0, 0, 255);
    squareClip.x = 0;
    squareClip.y = 0;
    squareClip.w = 300;
    squareClip.h = 300;
    // Init game objects
    square.init(0,0,0, &squareTexture, &squareClip);
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
    square.update();
}

void SceneTest::EventUpdate(SDL_Event *e) {
    square.eventUpdate(e);
}

void SceneTest::RenderUpdate() {
    square.render();
}
