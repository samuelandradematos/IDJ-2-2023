#include <iostream>
#include "Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music(const std::string& file) {
    music = nullptr;
    Open(file);
}

Music::~Music() {
    Stop(0);
    Mix_FreeMusic(music);
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    } else {
        std::cout << "Não há musica para tocar";
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(const std::string& file) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }

    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cout << SDL_GetError() << std::endl;
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

