#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
    tileW = tileWidth;
    tileH = tileHeight;
    GameObject* auxGO = new GameObject();

    tileSet = new Sprite((*auxGO),file);

    tileSet.Open(file);

    if (tileSet.IsOpen()) {
        columns = tileW/tileSet.GetWidth();
        rows = tileH/tileSet.GetHeight();
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    unsigned aux = columns * rows - 1;

    if (index <= aux) {
        tileSet.SetClip((int) x, (int) y, tileSet.GetWidth(), tileSet.GetHeight());
        tileSet.Render(x,y);
    }
}

int TileSet::GetTileHeight() {
    return tileH;
}

int TileSet::GetTileWidth() {
    return tileW;
}

