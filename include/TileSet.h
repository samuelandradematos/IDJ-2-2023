//
// Created by samuc on 20/09/2023.
//

#ifndef INCLUDE_TILESET_H_
#define INCLUDE_TILESET_H_
#include <string>
#include "Sprite.h"
#include "GameObject.h"

class TileSet {
    public:
        TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file);
        void RenderTile(unsigned index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();
    private:
        Sprite tileSet;
        int rows, columns, tileW, tileH;
};

#endif // INCLUDE_TILESET_H_
