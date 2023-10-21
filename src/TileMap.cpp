#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <sstream>


TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet) : Component(associated){
    Load(file);
    SetTileSet(tileSet);
    parallax = 0;
    started = false;
}

void TileMap::Load(const std::string& file) {
    std::ifstream map;
    map.open(file);


    std::fstream fileFS (file);
    if (map) {
        std::vector<std::string> dadosDaLinha;
        std::string linha, dado;
        int contaLinha = 0;

        while(std::getline(fileFS,linha)) {
            dadosDaLinha.clear();

            std::stringstream str(linha);

            while (std::getline(str, dado, ',')) {
                dadosDaLinha.push_back(dado);
            }

            if (contaLinha == 0) {
                mapWidth = stoi(dadosDaLinha[0]);
                mapHeight = stoi(dadosDaLinha[1]);
                mapDepth = stoi(dadosDaLinha[2]);
            }
            else {

                for (auto it: dadosDaLinha) {
                    tileMatrix.push_back(stoi(it) - 1);
                }
            }

            contaLinha++;

        }

    }
    else {
        std::cout << "Nao conseguiu abrir o arquivo." << std::endl;
    }
}

void TileMap::SetTileSet(TileSet *newTileSet) {
    tileSet = newTileSet;
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[x + (y * mapWidth) + (z * mapHeight * mapWidth)];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (auto x = 0; x < mapWidth; x++) {
        for (auto y = 0 ; y < mapHeight; y++) {
            tileSet->RenderTile(
                    At(x,y,layer),
                    (float) (x * tileSet->GetTileWidth() + cameraX),
                    (float) (y * tileSet->GetTileHeight()+ cameraY)
                    );
        }
    }

}

void TileMap::Render() {
    for (auto i = 0; i < mapDepth; i++) {
        RenderLayer(
                i,
                (int)Camera::pos.x * i * parallax,
                (int)Camera::pos.y * i * parallax
                );
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float dt) {}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

void TileMap::SetParallax(float plx) {
    parallax = plx;
}

void TileMap::Start() {}
