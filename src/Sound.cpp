#include <iostream>
#include "Sound.h"
#include "Resources.h"


Sound::Sound(GameObject& associated): Component(associated) {
    chunk = nullptr;
    started = false;
}

Sound::Sound(GameObject& associated, const std::string& file) : Component(associated) {
    Open(file);
    started = false;
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

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

Sound::~Sound() {}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(std::string type) {
    return type == "Sound";
}

void Sound::Start() {}

void Sound::NotifyCollision(GameObject &other) {}