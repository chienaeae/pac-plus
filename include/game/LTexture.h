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
#include <string>
#include <sstream>

#include "game/Resource.h"


class LTexture : public Resource{
public:
    LTexture();

    ~LTexture();

    bool LoadFromFile(std::string path) override;

#if defined(SDL_TTF_MAJOR_VERSION)

    bool LoadFromRenderedText(std::string text, SDL_Color color);

#endif

    void Free() override;

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);

    void SetBlendMode(SDL_BlendMode blending);

    void SetAlpha(Uint8 alpha);

    void Render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0,
                float scaleX = 1.0f, float scaleY = 1.0f, SDL_Point *center = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetWidth() const;

    int GetHeight() const;

private:
    SDL_Texture *mTexture;

    int mWidth;
    int mHeight;
};

#endif //MAIN_LTEXTURE_H
