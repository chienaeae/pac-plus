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

bool LTexture::loadFromRenderedText(const std::string text, const SDL_Color color) {
    free();
    if(!gFont.isOn()){
        printf("gFont is NULL pointer! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *textSurface = gFont.RenderTextSolid(text.c_str(), color);
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

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, float scaleX, float scaleY,
                      SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != nullptr) {
        renderQuad.w = clip->w * scaleX;
        renderQuad.h = clip->h * scaleY;
    }

    SDL_RenderCopyEx(gRenderer, this->mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() const{
    return mWidth;
}

int LTexture::getHeight() const{
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
