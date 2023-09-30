#include "InputManager.h"
#include <iostream>


InputManager::InputManager() :
mouseState{false, false, false, false, false, false},
mouseUpdate{0, 0, 0, 0, 0, 0},
quitRequested(false),
updateCounter(0),
mouseX(0),
mouseY(0) {}

InputManager::~InputManager() {}

void InputManager::Update() {
    // Union dos eventos
    SDL_Event event;

    // Captura a posição X e Y do mouse
    SDL_GetMouseState(&mouseX,&mouseY);

    // Atualiza o counter
    updateCounter++;

    while (SDL_PollEvent(&event)) {
        // Se o evento não for repetido
        if (event.key.repeat != 1) {
            switch (event.type) {
                // Seta flag de quit para true
                case SDL_QUIT:
                    quitRequested = true;
                    break;
                // Seta para true o valor da posição no vetor de estados e atualiza o vetor de update com o valor do counter;
                case SDL_MOUSEBUTTONDOWN:
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;
                // Seta para false o valor da posição no vetor de estados e atualiza o vetor de update com o valor do counter;
                case SDL_MOUSEBUTTONUP:
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;
                // Seta para true o valor da posição no vetor de estados e atualiza o vetor de update com o valor do counter
                // e caso a tecla seja ESC seta a flag de quit para true
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quitRequested = true;
                    }
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;
                // Seta para false o valor da posição no vetor de estados e atualiza o vetor de update com o valor do counter;
                case SDL_KEYUP:
                    keyState[event.key.keysym.sym] = false;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

            }
        }
    }

}

bool InputManager::KeyPress(int key) {
    return keyState.find(key) != keyState.end() && keyUpdate.find(key) != keyUpdate.end() && keyState.find(key)->second && keyUpdate.find(key)->second == updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return keyState.find(key) != keyState.end() && keyUpdate.find(key) != keyUpdate.end() && !keyState.find(key)->second && keyUpdate.find(key)->second == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    return keyState.find(key) != keyState.end() && keyState.find(key)->second;
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}
bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}
bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

InputManager& InputManager::GetInstance() {
    static InputManager im;
    return im;
}
