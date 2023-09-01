#include <iostream>
#include "Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music(const char* file) {
    music = nullptr;
    Open(file);
}

Music::~Music() {
    Stop(0);
    Mix_FreeMusic(music);
}

void Music::Play(int times = -1) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    } else {
        std::cout << "Não há musica para tocar";
    }
}

void Music::Stop(int msToStop = 1500) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(const char* file) {
    music = Mix_LoadMUS(file);
    if (music = nullptr) {
        std::cout << SDL_GetError();
    }
}

bool Music::IsOpen() {
    if (music != nullptr)
        return true;
    else
        return false
}

