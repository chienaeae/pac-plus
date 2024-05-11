//
// Created by mac on 2024/5/10.
//

#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

class Scene {

public:
    // Called when scene initially created. Called once.
    virtual void OnCreate() = 0;

    // Called when scene destroyed. Called at most once (if a scene
    // is not removed from the game, this will never be called).
    virtual void OnDestroy() = 0;

    // Called whenever a scene is transitioned into. Can be
    // called many times in a typical game cycle.
    virtual void OnActivate() {};

    // Called whenever a transition out of a scene occurs.
    // Can be called many times in a typical game cycle.
    virtual void OnDeactivate() {};

    virtual void EventUpdate(){};

    virtual void Update() {};

    virtual void RenderUpdate() {};
};

#endif //MAIN_SCENE_H
