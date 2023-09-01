#include "State.h"

State::State() {
    quitRequested = false;
    // cppcheck-suppress [noCopyConstructor,noOperatorEq]
    bg = new(Sprite);
    Music song("audio/stageStage.ogg");
    music = song;
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg->Render(1024, 768);
}

bool State::QuitRequested() {
    return quitRequested;
}
