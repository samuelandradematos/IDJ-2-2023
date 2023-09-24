#include "TileSet.h"
#include "iostream"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : tileSet (associated,file), tileW(tileWidth), tileH(tileHeight) {
    if (tileSet.IsOpen()) {
        columns = tileSet.GetWidth() / tileW;
        rows = tileSet.GetHeight() / tileH;

    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    unsigned aux = columns * rows - 1;

    if (index <= aux) {
        int xClip = tileW * (index % columns);
        int yClip = tileH * (index / columns);
        tileSet.SetClip(xClip, yClip, tileW, tileH);
        tileSet.Render(x,y);
    }
}

int TileSet::GetTileHeight() {
    return tileH;
}

int TileSet::GetTileWidth() {
    return tileW;
}

