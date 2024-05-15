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

auto LTexture::LoadFromFile(std::string tPath) -> bool {
    Free();

    SDL_Texture *newTexture = nullptr;

    // Option1:
    // newTexture = IMG_LoadTexture(gRenderer, path.c_str());

    // Option2:
    // 1. Create Surface
    // 2. Create Texture from Surface
    SDL_Surface *loadedSurface = IMG_Load(tPath.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << tPath.c_str() << "! SDL_Error: " << SDL_GetError()
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
            std::cout << "Unable to create texture from " << tPath.c_str() << "!\n";
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != nullptr;
}

auto LTexture::LoadFromRenderedText(const std::string &tText, const SDL_Color tColor) -> bool {
    Free();
    if (!gFont.isOn()) {
        std::cout << "gFont is NULL pointer! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_Surface *textSurface = gFont.RenderTextSolid(tText, tColor);
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

void LTexture::Render(int tX, int tY, SDL_Rect *tClip, double tAngle, float tScaleX, float tScaleY,
                      SDL_Point *tCenter, SDL_RendererFlip tFlip) {
    SDL_Rect renderQuad = {tX, tY, mWidth, mHeight};

    if (tClip != nullptr) {
        renderQuad.w = static_cast<int>(static_cast<float>(tClip->w) * tScaleX);
        renderQuad.h = static_cast<int>(static_cast<float>(tClip->h) * tScaleY);
    }

    SDL_RenderCopyEx(gRenderer, mTexture, tClip, &renderQuad, tAngle, tCenter, tFlip);
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

void LTexture::SetColor(Uint8 tRed, Uint8 tGreen, Uint8 tBlue) {
    SDL_SetTextureColorMod(mTexture, tRed, tGreen, tBlue);
}

void LTexture::SetBlendMode(SDL_BlendMode tBlending) {
    SDL_SetTextureBlendMode(mTexture, tBlending);
}

void LTexture::SetAlpha(Uint8 tAlpha) {
    SDL_SetTextureAlphaMod(mTexture, tAlpha);
}
