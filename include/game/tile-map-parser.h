//
// Created by mac on 5/22/24.
//

#ifndef PAC_PLUS_TILEMAPPARSER_H
#define PAC_PLUS_TILEMAPPARSER_H

#include <sstream>
#include <unordered_map>

#include "game/object.h"
#include "game/resource-allocator.h"
#include "game/texture.h"
#include "game/tile.h"
#include "game/vector2.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

using Layer = std::vector<std::shared_ptr<Tile>>;

// Stores layer names with layer.
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>;

// Stores the different tile types that can be used.
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;

struct TileSheetData {
    // The texture id will be retrieved by using our texture allocator.
    int textureID;            // The id of the tile sets texture.
    Vector2<uint> imageSize;  // The size of the texture.
    int columns;              // How many columns in the tile sheet.
    int rows;                 // How many rows in the tile sheet.
    Vector2<uint> tileSize;   // The size of an individual tile.
};

class TileMapParser {
   public:
    explicit TileMapParser(ResourceAllocator<Texture> &tTextureAllocator);

    auto Parse(const std::string &tMapFile, const std::string &tTileSetFile,
               const std::string &tSourceFile,
               Vector2<int> tOffset) -> std::vector<std::shared_ptr<Object>>;

   private:
    auto BuildTileSheetData(xml_node<> *tileSetNode,
                            const std::string &tSourceFile) -> std::shared_ptr<TileSheetData>;

    auto BuildMapTiles(xml_node<> *mapNode, xml_node<> *tileSetNode,
                       const std::string &tSourceFile) -> std::shared_ptr<MapTiles>;

    auto BuildLayer(xml_node<> *tLayerNode, const std::shared_ptr<TileSheetData> &tTileSheetData)
        -> std::pair<std::string, std::shared_ptr<Layer>>;

    ResourceAllocator<Texture> &mTextureAllocator;
};

#endif  // PAC_PLUS_TILEMAPPARSER_H
