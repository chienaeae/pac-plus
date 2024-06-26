//
// Created by mac on 2024/4/10.
//

#ifndef MAIN_CORE_H
#define MAIN_CORE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <sstream>
#include <string>

#include "game/font.h"

const int MILLISECOND = 1000;
const int SECOND = 1;

extern SDL_Renderer* gRenderer;
extern Font gFont;

#endif  // MAIN_CORE_H
