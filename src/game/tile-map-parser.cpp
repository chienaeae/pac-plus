//
// Created by mac on 5/23/24.
//

#include "game/tile-map-parser.h"

#include <iostream>

#include "game/component-sprite.h"
#include "game/utilities.h"
#include "game/vector2.h"

TileMapParser::TileMapParser(ResourceAllocator<Texture> &tTextureAllocator)
    : mTextureAllocator(tTextureAllocator) {}

auto TileMapParser::Parse(const std::string &tMapFile, const std::string &tTileSetFile,
                          const std::string &tSourceFile,
                          Vector2<int> tOffset) -> std::vector<std::shared_ptr<Object>> {
    auto mapFileLocationOwner = std::make_unique<char[]>(
        tMapFile.size() + 1);  // NOLINT(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
    char *mapFileLocation = mapFileLocationOwner.get();
    auto tileSetFileLocationOwner = std::make_unique<char[]>(
        tTileSetFile.size() +
        1);  // NOLINT(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
    char *tileSetFileLocation = tileSetFileLocationOwner.get();

    // TODO: make multi format version of string copy
#ifdef MACOS
    strlcpy(mapFileLocation, tMapFile.c_str(), tMapFile.size() + 1);
    strlcpy(tileSetFileLocation, tTileSetFile.c_str(), tTileSetFile.size() + 1);
#else
    strcpy_s(mapFileLocation, tMapFile.size() + 1, tMapFile.c_str());
    strcpy_s(tileSetFileLocation, tTileSetFile.size() + 1, tTileSetFile.c_str());
#endif

    // TODO: error checking - check map & tileSet file exists before attempting open.
    rapidxml::file<> xmlMapFile(mapFileLocation);
    rapidxml::file<> xmlTileSetFile(tileSetFileLocation);

    rapidxml::xml_document<> mapDoc;
    mapDoc.parse<0>(xmlMapFile.data());
    xml_node<> *mapNode = mapDoc.first_node("map");

    rapidxml::xml_document<> tileSetDoc;
    tileSetDoc.parse<0>(xmlTileSetFile.data());
    xml_node<> *tileSetNode = tileSetDoc.first_node("tileset");

    // Loads tile layers from XML
    std::shared_ptr<MapTiles> tiles = BuildMapTiles(mapNode, tileSetNode, tSourceFile);

    // We need these to calculate the tiles position in world space
    int tileSizeX = std::atoi(mapNode->first_attribute("tilewidth")->value());
    int tileSizeY = std::atoi(mapNode->first_attribute("tileheight")->value());
    //    int mapsizeX = std::atoi(mapNode->first_attribute("width")->value());
    //    int mapsizeY = std::atoi(mapNode->first_attribute("height")->value());

    // This will contain all of our tiles as objects
    std::vector<std::shared_ptr<Object>> tileObjects;

    // We iterate through each layer in the tile map
    for (const auto &layer : *tiles) {
        for (const auto &tile : *layer.second) {
            std::shared_ptr<TileInfo> tileInfo = tile->properties;

            std::shared_ptr<Object> tileObject = std::make_shared<Object>();

            // TODO: tile scale should be set at the data level.
            const float tileScale = 3.0f;

            // Allocate sprite
            auto sprite = tileObject->AddComponent<ComponentSprite>();
            sprite->SetTextureAllocator(&mTextureAllocator);
            sprite->Load(tileInfo->textureID);
            sprite->SetTextureRect(tileInfo->textureRect);
            sprite->Scale(tileScale, tileScale);

            // Calculate world position
            int x = static_cast<int>(static_cast<float>(tile->x) * static_cast<float>(tileSizeX) *
                                     tileScale) +
                    tOffset.X;
            int y = static_cast<int>(static_cast<float>(tile->y) * static_cast<float>(tileSizeY) *
                                     tileScale) +
                    tOffset.Y;
            tileObject->Transform->SetPosition(x, y);

            tileObjects.emplace_back(tileObject);
        }
    }

    return tileObjects;
}

auto TileMapParser::BuildMapTiles(xml_node<> *mapNode, xml_node<> *tileSetNode,
                                  const std::string &tSourceFile) -> std::shared_ptr<MapTiles> {
    std::shared_ptr<TileSheetData> tileSheetData = BuildTileSheetData(tileSetNode, tSourceFile);

    std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();

    for (xml_node<> *node = mapNode->first_node("layer"); node; node = node->next_sibling()) {
        std::pair<std::string, std::shared_ptr<Layer>> mapLayer = BuildLayer(node, tileSheetData);
        map->emplace(mapLayer);
    }

    return map;
}

auto TileMapParser::BuildTileSheetData(xml_node<> *tileSetNode, const std::string &tSourceFile)
    -> std::shared_ptr<TileSheetData> {
    TileSheetData tileSheetData{};

    // TODO: add error checking to ensure these values actually exist.
    // TODO: add support for multiple tile sets.
    // TODO: implement this.
    //    int firstID = std::atoi(tileSheetNode->first_attribute("firstgid")->value());

    // Build the tile set data
    tileSheetData.tileSize.X = std::atoi(tileSetNode->first_attribute("tilewidth")->value());
    tileSheetData.tileSize.Y = std::atoi(tileSetNode->first_attribute("tileheight")->value());
    int tileCount = std::atoi(tileSetNode->first_attribute("tilecount")->value());
    tileSheetData.columns = std::atoi(tileSetNode->first_attribute("columns")->value());
    tileSheetData.rows = tileCount / tileSheetData.columns;

    xml_node<> *imageNode = tileSetNode->first_node("image");
    tileSheetData.imageSize.X = std::atoi(imageNode->first_attribute("width")->value());
    tileSheetData.imageSize.Y = std::atoi(imageNode->first_attribute("height")->value());

    tileSheetData.textureID = mTextureAllocator.Add(tSourceFile);

    return std::make_shared<TileSheetData>(tileSheetData);
}

auto TileMapParser::BuildLayer(xml_node<> *tLayerNode,
                               const std::shared_ptr<TileSheetData> &tTileSheetData)
    -> std::pair<std::string, std::shared_ptr<Layer>> {
    TileSet tileSet;
    std::shared_ptr<Layer> layer = std::make_shared<Layer>();

    int width = std::atoi(tLayerNode->first_attribute("width")->value());
    //    int height = std::atoi(tLayerNode->first_attribute("height")->value());

    xml_node<> *dataNode = tLayerNode->first_node("data");
    char *mapIndices = dataNode->value();

    std::stringstream fileStream(mapIndices);

    int count = 0;

    //    std::string line;
    while (fileStream.good()) {
        std::string substr;
        std::getline(fileStream, substr, ',');

        if (!Utilities::IsInteger(substr)) {
            // We remove special characters from the int before parsing
            substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end());
            substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end());

            // TODO: add additional check to
            // confirm that the character removals have worked:
        }

        int tileID = std::stoi(substr);

        if (tileID != 0) {
            auto itr = tileSet.find(tileID);
            // if not tile is found in tileSet
            if (itr == tileSet.end()) {
                // calculate the x and y position in tile source
                int textureX = tileID % tTileSheetData->columns != 0
                                   ? tileID % tTileSheetData->columns - 1
                                   : tTileSheetData->columns - 1;
                int textureY = (tileID - 1) / tTileSheetData->columns;

                std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(
                    tTileSheetData->textureID, tileID,
                    SDL_Rect{static_cast<int>(textureX * tTileSheetData->tileSize.X),
                             static_cast<int>(textureY * tTileSheetData->tileSize.Y),
                             static_cast<int>(tTileSheetData->tileSize.X),
                             static_cast<int>(tTileSheetData->tileSize.Y)});

                itr = tileSet.insert(std::make_pair(tileID, tileInfo)).first;
            }

            std::shared_ptr<Tile> tile = std::make_shared<Tile>();

            tile->properties = itr->second;
            tile->x = count % width;
            tile->y = count / width;

            layer->emplace_back(tile);
        }

        count++;
    }

    const std::string layerName = tLayerNode->first_attribute("name")->value();
    return std::make_pair(layerName, layer);
}
