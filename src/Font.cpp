//
// Created by mac on 2024/5/12.
//

#include "game/Font.h"

#include <SDL_error.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>

#include <cstdio>
#include <iostream>
#include <string>

const int DEFAULT_FONT_SIZE = 24;
Font::Font() : mFont(nullptr), mFontSize(DEFAULT_FONT_SIZE), mFontStyle(FONT_STYLE::NORMAL) {}

auto Font::RenderTextSolid(const std::string &tText, SDL_Color tFG) -> SDL_Surface * {
    SDL_Surface *textSurface = TTF_RenderText_Solid(mFont, tText.c_str(), tFG);
    if (textSurface == nullptr) {
        std::cout << "SDL_Surface could not initialized! SDL_Error: " << SDL_GetError() << "\n";
        return nullptr;
    }

    return textSurface;
}

auto Font::LoadFromFile(std::string tPath) -> bool {
    Free();

    bool success = false;
    mFont = TTF_OpenFont(tPath.c_str(), mFontSize);
    if (mFont == nullptr) {
        std::cout << "Global Font could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return success;
    }
    mIsOn = 1;

    success = true;
    return success;
}

auto Font::SetFontSize(int tSize) -> bool {
    bool const success = TTF_SetFontSize(mFont, tSize) != 0;
    if (!success) {
        return success;
    }
    mFontSize = tSize;
    return success;
}

void Font::SetStyle(FONT_STYLE tStyle) {
    switch (tStyle) {
        case NORMAL:
            TTF_SetFontStyle(mFont, TTF_STYLE_NORMAL);
            break;
        case BOLD:
            TTF_SetFontStyle(mFont, TTF_STYLE_BOLD);
            break;
        case ITALIC:
            TTF_SetFontStyle(mFont, TTF_STYLE_ITALIC);
            break;
        case UNDERLINE:
            TTF_SetFontStyle(mFont, TTF_STYLE_UNDERLINE);
            break;
        case STRIKETHROUGH:
            TTF_SetFontStyle(mFont, TTF_STYLE_STRIKETHROUGH);
            break;
    }
    mFontStyle = tStyle;
}

void Font::Free() {
    TTF_CloseFont(mFont);
    mIsOn = 0;
}
