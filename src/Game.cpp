#include <iostream>
#include "Game.h"
#include "Resources.h"


Game* Game::instance = nullptr;

Game::Game(std::string title, int width , int height) {
    if (instance == nullptr) {
        instance = this;
        int stopCond = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
        if (stopCond != 0) {
            std::cout << "SDL_INIT: " << SDL_GetError() << std::endl;
        }
        stopCond = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
        if (stopCond != (IMG_INIT_JPG | IMG_INIT_PNG)) {
            std::cout << "IMG_INIT: " << SDL_GetError() << std::endl;
        }
        stopCond = Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MP3);
        if ( stopCond != (MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MP3) ) {
            std::cout << "MIX_INIT: " << Mix_GetError() << std::endl;
        }
        stopCond = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        if (stopCond != 0) {
            std::cout << "MIX_OPENAUDIO: " << Mix_GetError() << std::endl;
        }
        stopCond = Mix_AllocateChannels(32);
        if (stopCond < 32) {
            std::cout << "MIX_ALLOCATECHANNELS: " << Mix_GetError() << std::endl;
        }

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if (window == nullptr) {
            std::cout << "SDL_CREATEWINDOW: " << SDL_GetError() << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            std::cout << "SDL_CREATERENDERER: " << SDL_GetError() << std::endl;
        }

        frameStart = 0;
        dt = 0;
    }
}

Game::~Game() {
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
    state = new State();
    InputManager& im = InputManager::GetInstance();
    state->Start();
    while (!state->QuitRequested()) {
        CalculateDeltaTime();
        im.Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
    Resources::ClearSounds();
    Resources::ClearMusics();
    Resources::ClearImages();
    delete instance;
}

Game& Game::GetInstance() {
    if (instance != nullptr) {
        return *instance;
    } else {
        instance = new Game("Samuel_Andrade_de_Matos_170155943", 1024, 600);
        return *instance;
    }
}

void Game::CalculateDeltaTime() {
    int frameNow = SDL_GetTicks();

    dt = (frameNow - frameStart) / 1000.0;

    frameStart = frameNow;
}

float Game::GetDeltaTime() {
    return dt;
}