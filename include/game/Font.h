//
// Created by mac on 2024/5/12.
//

#ifndef MAIN_FONT_H
#define MAIN_FONT_H

#include <SDL_ttf.h>

#include "game/Resource.h"

enum FONT_STYLE { NORMAL, BOLD, ITALIC, UNDERLINE, STRIKETHROUGH };

class Font : public Resource {
   public:
    Font();

    ~Font() = default;

    SDL_Surface* RenderTextSolid(const std::string& text, SDL_Color fg);

    bool LoadFromFile(std::string path) override;

    bool SetFontSize(int size);

    void SetStyle(FONT_STYLE style);

    void Free() override;

   private:
    int mFontSize;
    FONT_STYLE mFontStyle;
    TTF_Font* mFont;
};

#endif  // MAIN_FONT_H
