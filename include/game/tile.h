//
// Created by mac on 5/22/24.
//

#ifndef PAC_PLUS_TILE_H
#define PAC_PLUS_TILE_H

#include "SDL.h"
#include "game/resource-allocator.h"

struct TileInfo {
    TileInfo() : tileID(-1) {}

    TileInfo(int tTextureID, unsigned int tTileID, SDL_Rect tTextureRect)
        : textureID(tTextureID), tileID(tTileID), textureRect(tTextureRect) {}

    int tileID;
    int textureID;
    SDL_Rect textureRect;
};

struct Tile {
    std::shared_ptr<TileInfo> properties;
    int x;
    int y;
};

#endif  // PAC_PLUS_TILE_H
