#include "State.h"

State::State():bg("Recursos/img/ocean.jpg"), music("Recursos/audio/stageState.ogg") {
    quitRequested = false;
    music.Play();
}

State::~State() {
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}
