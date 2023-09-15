#include <iostream>
#include "Sound.h"


Sound::Sound(GameObject& associated): Component(associated) {
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, const char* file) : Sound(associated) {
    Open(file);
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if (channel == -1) {
        std::cout << "Não há canais desponiveis." << std::endl;
    }
}

void Sound::Stop() {
    int aux = Mix_HaltChannel(channel);
    if (aux == -1) {
        std::cout << SDL_GetError() << std::endl;
    }
}

void Sound::Open(const char* file) {
    chunk = Mix_LoadWAV(file);
    if (chunk == nullptr) {
        std::cout << SDL_GetError() << std::endl;
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Sound::Stop();
        Mix_FreeChunk(chunk);
    } else {
        Mix_FreeChunk(chunk);
    }
}

void Sound::Update(float dt) {
}

void Sound::Render() {}

bool Sound::Is(std::string type) {
    return type == "Sound";
}


