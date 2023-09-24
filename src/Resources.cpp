#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    if (imageTable.find(file) != imageTable.end()) {
        return imageTable.find(file)->second;
    }
    Game& game = Game::GetInstance();
    SDL_Texture* aux = IMG_LoadTexture(game.GetRenderer(), file.c_str());
    if (aux == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return aux;
    }
    imageTable.insert({file,aux});
    return aux;
}

void Resources::ClearImages() {
    for (auto it : imageTable) {
        SDL_DestroyTexture(it.second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    if (musicTable.find(file) != musicTable.end()) {
        return musicTable.find(file)->second;
    }
    Mix_Music* aux = Mix_LoadMUS(file.c_str());
    if (aux == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return nullptr;
    }
    musicTable.insert({file,aux});
    return aux;
}

void Resources::ClearMusics() {
    for (auto it : musicTable) {
        Mix_FreeMusic(it.second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
    if (soundTable.find(file) != soundTable.end()) {
        return soundTable.find(file)->second;
    }

    Mix_Chunk* aux = Mix_LoadWAV(file.c_str());
    if (aux == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return nullptr;
    }
    soundTable.insert({file,aux});
    return aux;
}

void Resources::ClearSounds() {
    for (auto it : soundTable) {
        Mix_FreeChunk(it.second);
    }
    soundTable.clear();
}