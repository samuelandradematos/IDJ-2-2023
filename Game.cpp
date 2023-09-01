
#include "Game.h"

namespace std{

Game::Game(const char* title, int width , int height) {
    if (instance != nullptr) {
        this->instance;
    } else {
        int stopCond = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
        if (stopCond != 0) {
            cout << SDL_GetError();
            return;
        }
        stopCond = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        if (stopCond = 0) {
            cout << "Image not loaded";
            return;
        }
        stopCond = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        if (stopCond != 0) {
            cout << SDL_GetError();
            return;
        }
        Mix_AllocateChannels(32);
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        // cppcheck-suppress [noCopyConstructor,noOperatorEq]
        state = new(State);
        instance = this;
    }
}

Game::~Game() {
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

State* Game::GetState() {
    return state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    while (true) {
        state->Update(1.0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}

Game& Game::GetInstance(){
    if (instance != nullptr) {
        return *instance;
    } else {
        // instance = new(Game)
        return (*instance);
    }
}

};  // namespace std
