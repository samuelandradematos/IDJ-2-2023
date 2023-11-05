#include <iostream>
#include "Game.h"
#include "Resources.h"
#include "InputManager.h"


Game* Game::instance = nullptr;

Game::Game(std::string title, int width , int height) : storedState(nullptr), frameStart(0), dt(0) {
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

        stopCond = TTF_Init();
        if (stopCond != 0) {
            std::cout << "TTF_INIT: " << SDL_GetError() << std::endl;
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
    }
}

Game::~Game() {
    if (storedState != nullptr){
        delete storedState;
    }

    while (!stateStack.empty()) {
            stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();

    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State &Game::GetCurrentState() {
    return *stateStack.top();
}

void Game::Push(State *state) {
    storedState = state;
}

void Game::Run() {
    if (storedState != nullptr) {
        stateStack.push((std::unique_ptr<State>)storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    } else {
        return;
    }

    while (!stateStack.empty()) {
        if (stateStack.top()->QuitRequested()) {
            stateStack.top()->Pause();
            stateStack.pop();
        }

        if (stateStack.top()->PopRequested()) {
            stateStack.top()->Pause();
            stateStack.pop();

            if (!stateStack.empty()) {
                stateStack.top()->Resume();
            }
        }

        if (storedState != nullptr) {
            if (!stateStack.empty()) {
                stateStack.top()->Pause();
            }
            stateStack.push((std::unique_ptr<State>)storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }

        if (!stateStack.empty()) {
            CalculateDeltaTime();
            InputManager::GetInstance().Update();
            stateStack.top()->Update(dt);
            stateStack.top()->Render();
            SDL_RenderPresent(renderer);
            SDL_Delay(33);
        } else {
            break;
        }
    }

    Resources::ClearSounds();
    Resources::ClearMusics();
    Resources::ClearImages();
    Resources::ClearFonts();
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

Vec2 Game::GetWindowCenter() {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window,&windowWidth,&windowHeight);
    Vec2 aux = Vec2(windowWidth / 2,windowHeight / 2);
    return aux;
}
