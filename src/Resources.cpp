#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

SDL_Texture* Resources::GetImage(std::string file) {
    if (imageTable.find(file) != imageTable.end()) {
        return imageTable.find(file)->second;
    }
    SDL_Texture* aux = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (aux == nullptr) {
        std::cout << SDL_GetError() << std::endl;
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

TTF_Font* Resources::GetFont(std::string file, int pointSize) {
    std::string sizeString = " ";
    sizeString.append(std::to_string(pointSize));
    std::string fontFileIndexed = file;
    fontFileIndexed.append(sizeString);

    try {
        if (fontTable.find(fontFileIndexed) != fontTable.end()) {
            return fontTable.find(fontFileIndexed)->second;
        }

        TTF_Font *auxFont = TTF_OpenFont(file.c_str(), pointSize);
        if (auxFont == nullptr) {
            std::cout << SDL_GetError() << std::endl;
            throw std::runtime_error("Failed to load font file " + file);
        }

        fontTable.insert({fontFileIndexed, auxFont});
        return auxFont;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr;
    }
}

void Resources::ClearFonts() {
    for (const auto & it : fontTable){
        TTF_CloseFont(it.second);
    }

    fontTable.clear();
}