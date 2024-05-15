//
// Created by mac on 2024/4/10.
//

#ifndef MAIN_LTEXTURE_H
#define MAIN_LTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <sstream>
#include <string>

#include "game/resource.h"

class Texture : public Resource {
   public:
    Texture();

    ~Texture() = default;

    auto LoadFromFile(std::string path) -> bool override;

#if defined(SDL_TTF_MAJOR_VERSION)

    auto LoadFromRenderedText(const std::string &tText, SDL_Color tColor) -> bool;

#endif

    void Free() override;

    void SetColor(Uint8 tRed, Uint8 tGreen, Uint8 tBlue);

    void SetBlendMode(SDL_BlendMode blending);

    void SetAlpha(Uint8 alpha);

    void Render(int tX, int tY, SDL_Rect *tClip = nullptr, double tAngle = 0.0,
                float tScaleX = 1.0f, float tScaleY = 1.0f, SDL_Point *tCenter = nullptr,
                SDL_RendererFlip tFlip = SDL_FLIP_NONE);

    auto GetWidth() const -> int;

    auto GetHeight() const -> int;

   private:
    SDL_Texture *mTexture{nullptr};

    int mWidth{0};
    int mHeight{0};
};

#endif  // MAIN_LTEXTURE_H
