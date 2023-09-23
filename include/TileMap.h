#ifndef INCLUDE_TILEMAP_H_
#define INCLUDE_TILEMAP_H_
#include <string>
#include <vector>
#include "TileSet.h"

class TileMap : public Component {
    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);
        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};

#endif  // INCLUDE_TILEMAP_H_