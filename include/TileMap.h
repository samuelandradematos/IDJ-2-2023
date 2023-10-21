#ifndef INCLUDE_TILEMAP_H_
#define INCLUDE_TILEMAP_H_
#include <string>
#include <vector>
#include "TileSet.h"

class TileMap : public Component {
    public:
        TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);
        void Load(const std::string& file);
        void SetTileSet(TileSet* newTileSet);
        int& At(int x, int y, int z = 0);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Start();
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();
        void SetParallax(float parallax);
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
        float parallax;
        bool started;
};

#endif  // INCLUDE_TILEMAP_H_