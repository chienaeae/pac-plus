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
#include <iostream>
#include <string>

#include "game/Core.h"

LTexture::LTexture() = default;

auto LTexture::LoadFromFile(std::string path) -> bool {
    Free();

    SDL_Texture *newTexture = nullptr;

    // Option1:
    // newTexture = IMG_LoadTexture(gRenderer, path.c_str());

    // Option2:
    // 1. Create Surface
    // 2. Create Texture from Surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_Error: " << SDL_GetError()
                  << "\n";
    } else {
        const int PIXEL_COLOR_R = 0;
        const int PIXEL_COLOR_G = 0xFF;
        const int PIXEL_COLOR_B = 0xFF;
        SDL_SetColorKey(
            loadedSurface, SDL_TRUE,
            SDL_MapRGB(loadedSurface->format, PIXEL_COLOR_R, PIXEL_COLOR_G, PIXEL_COLOR_B));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from " << path.c_str() << "!\n";
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != nullptr;
}

auto LTexture::LoadFromRenderedText(const std::string &text, const SDL_Color color) -> bool {
    Free();
    if (!gFont.isOn()) {
        std::cout << "gFont is NULL pointer! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_Surface *textSurface = gFont.RenderTextSolid(text, color);
    if (textSurface == nullptr) {
        std::cout << "SDL_Surface could not initialized! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (mTexture == nullptr) {
        std::cout << "SDL_Texture could not initialized! SDL_Error: " << SDL_GetError() << "\n";
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
        renderQuad.w = static_cast<int>(static_cast<float>(clip->w) * scaleX);
        renderQuad.h = static_cast<int>(static_cast<float>(clip->h) * scaleY);
    }

    SDL_RenderCopyEx(gRenderer, this->mTexture, clip, &renderQuad, angle, center, flip);
}

auto LTexture::GetWidth() const -> int {
    return mWidth;
}

auto LTexture::GetHeight() const -> int {
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
