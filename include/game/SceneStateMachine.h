//
// Created by mac on 2024/5/10.
//

#ifndef MAIN_SCENESTATEMACHINE_H
#define MAIN_SCENESTATEMACHINE_H

#include <SDL.h>
#include <game/Scene.h>

#include <memory>
#include <unordered_map>

class SceneStateMachine {
   public:
    SceneStateMachine();

    void EventUpdate(SDL_Event* tEvent);

    void Update(float tDeltaTime);

    void LateUpdate(float tDeltaTime);

    void RenderUpdate();

    unsigned int Add(const std::shared_ptr<Scene>& tScene);

    void SwitchTo(unsigned int tID);

    void Remove(unsigned int tID);

   private:
    std::unordered_map<unsigned int, std::shared_ptr<Scene>> mScenes;

    std::shared_ptr<Scene> mCurrentScene;

    unsigned int mInsertedSceneID;
};

#endif  // MAIN_SCENESTATEMACHINE_H
