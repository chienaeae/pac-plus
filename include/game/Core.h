//
// Created by mac on 2024/4/10.
//

#ifndef MAIN_CORE_H
#define MAIN_CORE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

#endif //MAIN_CORE_H
