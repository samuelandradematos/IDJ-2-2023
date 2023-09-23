#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <sstream>

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet) : Component(associated){
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(const std::string& file) {
    std::ifstream map;
    map.open(file);
    std::vector<std::string> dadosDaLinha;
    std::string linha, dado; 
    int contaLinha = 0;

    if (map.is_open()) {
        while(map.getline(linha)) {
            dadosDaLinha.clear();

            std::stringstream str(linha);

            while (std::getline(str, dado, ','))
                dadosDaLinha.push_back(dado);
            
            if (contaLinha == 0) {
                mapWidth = stoi(dadosDaLinha[0]);
                mapHeight = stoi(dadosDaLinha[1]);
                mapDepth = stoi(dadosDaLinha[2]);
            }

            for (auto it :dadosDaLinha) {
                tileMatrix.push_back(stoi(it));
            }

            contaLinha++;

        }

    }
    else {
        std::cout << "Nao conseguiu abrir o arquivo." << std::endl;
    }
}