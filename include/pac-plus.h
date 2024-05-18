//
// Created by mac on 5/15/24.
//

#ifndef PAC_PLUS_PAC_PLUS_H
#define PAC_PLUS_PAC_PLUS_H

#include "game/game.h"

class PacPlus : public Game {
   public:
    void OnCreate() final;

    void Update(float deltaTime) final;

    void LateUpdate(float deltaTime) final;

    void RenderUpdate(SDL_Renderer* tRenderer) final;

    void EventUpdate(SDL_Event* tEvent) final;

   private:
    SceneStateMachine mSceneStateMachine;

    ResourceAllocator<Texture> mTextureAllocator;
};

#endif  // PAC_PLUS_PAC_PLUS_H
