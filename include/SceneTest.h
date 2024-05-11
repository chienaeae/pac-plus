//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_SCENETEST_H
#define MAIN_SCENETEST_H

#include "game/Scene.h"
#include "game/SceneStateMachine.h"

class SceneTest: public Scene {
public :
    SceneTest(SceneStateMachine& sceneStateMachine);

    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;

    void Update() override;
    void RenderUpdate() override;

    void SetSwitchToScene(unsigned int id );

private:
    SceneStateMachine& sceneStateMachine;

    // How long the scene has currently been visible
    float currentSeconds;

    unsigned int switchToState;
};

#endif //MAIN_SCENETEST_H
