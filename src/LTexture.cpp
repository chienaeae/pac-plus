//
// Created by mac on 2024/4/10.
//

#include "game/LTexture.h"

#include <SDL_blendmode.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>

#include <cstdio>
#include <string>

#include "game/Core.h"

LTexture::LTexture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

bool LTexture::LoadFromFile(std::string path) {
    Free();

    SDL_Texture *newTexture = nullptr;

    // Option1:
    // newTexture = IMG_LoadTexture(gRenderer, path.c_str());

    // Option2:
    // 1. Create Surface
    // 2. Create Texture from Surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            printf("Unable to create texture from %s!", path.c_str());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != nullptr;
}

bool LTexture::LoadFromRenderedText(const std::string &text, const SDL_Color color) {
    Free();
    if (!gFont.isOn()) {
        printf("gFont is NULL pointer! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *textSurface = gFont.RenderTextSolid(text, color);
    if (textSurface == nullptr) {
        printf("SDL_Surface could not initialized! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (mTexture == nullptr) {
        printf("SDL_Texture could not initialized! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

    return true;
}

void LTexture::Render(int x, int y, SDL_Rect *clip, double angle, float scaleX, float scaleY,
                      SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != nullptr) {
        renderQuad.w = (int)((float)clip->w * scaleX);
        renderQuad.h = (int)((float)clip->h * scaleY);
    }

    SDL_RenderCopyEx(gRenderer, this->mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::GetWidth() const {
    return mWidth;
}

int LTexture::GetHeight() const {
    return mHeight;
}

void LTexture::Free() {
    SDL_DestroyTexture(mTexture);
}

void LTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::SetBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::SetAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}
