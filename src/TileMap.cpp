#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <sstream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(std::string file) {
    std::ifstream map;
    map.open(file);
    std::vector<std::string> dadosDaLinha;
    std::string linha, dado; 
    int contaLinha = 0;

    if (map.is_open()) {
        while(std::getline(file,linha)) {
            dadosDaLinha.clear();

            std::stringstream str(linha);

            while (std::getline(str, dado, ','))
                dadosDaLinha.push_back(dado);
            
            if (contaLinha == 0) {
                for (auto it = dadosDaLinha.begin(); it < dadosDaLinha.end(); it++) {
                    
                }
            }

        }

    }
    else {
        std::cout << "Nao conseguiu abrir o arquivo." << std::endl;
    }
}