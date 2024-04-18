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


class LTexture {
public:
    LTexture();

    ~LTexture();

    bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)

    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

#endif

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

    void render(int x, int y, SDL_Rect *clip = nullptr,
                double angle = 0.0, SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();

    int getHeight();

private:
    SDL_Texture *mTexture;

    int mWidth;
    int mHeight;
};

#endif //MAIN_LTEXTURE_H
