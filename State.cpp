#include "State.h"
namespace std {

State::State() {
    quitRequested = false;
    // cppcheck-suppress [noCopyConstructor,noOperatorEq]
    bg = new(Sprite);
    music = new(Music);
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

}  // namespace std
