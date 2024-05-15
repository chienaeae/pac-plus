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

auto Font::RenderTextSolid(const std::string &text, SDL_Color fg) -> SDL_Surface * {
    SDL_Surface *textSurface = TTF_RenderText_Solid(mFont, text.c_str(), fg);
    if (textSurface == nullptr) {
        std::cout << "SDL_Surface could not initialized! SDL_Error: " << SDL_GetError() << "\n";
        return nullptr;
    }

    return textSurface;
}

auto Font::LoadFromFile(std::string path) -> bool {
    Free();

    bool success = false;
    mFont = TTF_OpenFont(path.c_str(), mFontSize);
    if (mFont == nullptr) {
        std::cout << "Global Font could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return success;
    }
    mIsOn = 1;

    success = true;
    return success;
}

auto Font::SetFontSize(int size) -> bool {
    bool const success = TTF_SetFontSize(mFont, size) != 0;
    if (!success) {
        return success;
    }
    mFontSize = size;
    return success;
}

void Font::SetStyle(FONT_STYLE style) {
    switch (style) {
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
    mFontStyle = style;
}

void Font::Free() {
    TTF_CloseFont(mFont);
    mIsOn = 0;
}
