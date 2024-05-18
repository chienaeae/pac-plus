//
// Created by mac on 5/15/24.
//

#ifndef PAC_PLUS_WINDOW_H
#define PAC_PLUS_WINDOW_H

#include <SDL.h>

#include <string>

#include "game/fps.h"
#include "game/timer.h"

class Window {
   public:
    Window();

    auto Init(const std::string &tName, int tWidth, int tHeight) -> int;

    void BeginDraw();

    void Draw();

    void EndDraw();

    void Close();

    auto GetRenderer() -> SDL_Renderer *;

    auto IsOpen() const -> bool;

   private:
    bool mIsOpen;

    SDL_Window *mWindow;
};

#endif  // PAC_PLUS_WINDOW_H
