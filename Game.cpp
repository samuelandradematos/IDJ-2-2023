#include "Game.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "src/include/SDL2/SDL_include.h"

namespace std{

Game::Game(string title, int width , int height) {
    int stopCond;
    if (instance != nullptr) {
        this->instance;
    } else {
        stopCond = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
        if (stopCond != 0) {
            
        }
        this->this;
    }
}

Game& Game::GetInstance(){
    if (Game.instance != nullptr) {
        return *instance;
    }
    else{
        *instance = new(Game);
        return (*instance)
    }
}

};  // namespace std
