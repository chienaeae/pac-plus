//
// Created by mac on 2024/5/12.
//

#ifndef MAIN_FONT_H
#define MAIN_FONT_H

#include <SDL_ttf.h>

#include "game/resource.h"

enum FONT_STYLE { NORMAL, BOLD, ITALIC, UNDERLINE, STRIKETHROUGH };

class Font : public Resource {
   public:
    Font();

    ~Font() = default;

    SDL_Surface* RenderTextSolid(const std::string& tText, SDL_Color tFG);

    bool LoadFromFile(std::string tPath) override;

    bool SetFontSize(int tSize);

    void SetStyle(FONT_STYLE tStyle);

    void Free() override;

   private:
    int mFontSize;
    FONT_STYLE mFontStyle;
    TTF_Font* mFont;
};

#endif  // MAIN_FONT_H
