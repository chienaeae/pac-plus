//
// Created by mac on 2024/4/10.
//

#include "game/Core.h"
#include "game/LTexture.h"

LTexture::LTexture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(std::string path) {
    free();

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
            printf("Unable to create textrue from %s!", path.c_str());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != nullptr;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
    free();

    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface == nullptr) {
        printf("\n");
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (mTexture == nullptr) {
        printf("\n");
        return false;
    }
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

    return true;
}

void LTexture::render(int x, int y, SDL_Rect *clip,
                      double angle, SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, this->mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

void LTexture::free() {
    SDL_DestroyTexture(mTexture);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}
