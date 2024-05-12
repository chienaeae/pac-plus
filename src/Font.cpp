//
// Created by mac on 2024/5/12.
//

#include <SDL_ttf.h>

#include "game/Font.h"

Font::Font(): mFont(nullptr), mFontSize(24), mFontStyle(FONT_STYLE::NORMAL){
}

Font::~Font(){
}

SDL_Surface * Font::RenderTextSolid(std::string text, SDL_Color fg) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(mFont, text.c_str(), fg);
    if (textSurface == nullptr) {
        printf("SDL_Surface could not initialized! SDL_Error: %s\n", SDL_GetError());
        return nullptr;
    }

    return textSurface;
}

bool Font::LoadFromFile(std::string path) {
    bool success = false;
    mFont = TTF_OpenFont(path.c_str(), mFontSize);
    if(mFont == nullptr){
        printf("Global Font could not be created! SDL_Error: %s\n", SDL_GetError());
        return success;
    }
    mIsOn = true;

    success = true;
    return success;
}

bool Font::SetFontSize(int size) {
    bool success = TTF_SetFontSize(mFont, size);
    if(!success) {
        return success;
    }
    mFontSize = size;
    return success;
}


void  Font::SetStyle(FONT_STYLE style){
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
    mIsOn = false;
}
