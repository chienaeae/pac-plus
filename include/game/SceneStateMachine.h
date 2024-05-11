//
// Created by mac on 2024/5/10.
//

#ifndef MAIN_SCENESTATEMACHINE_H
#define MAIN_SCENESTATEMACHINE_H

#include <SDL.h>
#include <memory>
#include <unordered_map>

#include <game/Scene.h>

class SceneStateMachine {
public:
    SceneStateMachine();

    void EventUpdate(SDL_Event *e);

    void Update(float deltaTime);

    void LateUpdate(float deltaTime);

    void RenderUpdate();

    unsigned int Add(std::shared_ptr<Scene> scene);

    void SwitchTo(unsigned int id);

    void Remove(unsigned int id);

private :
    std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;

    std::shared_ptr<Scene> currentScene;

    unsigned int insertedSceneID;
};

#endif //MAIN_SCENESTATEMACHINE_H
