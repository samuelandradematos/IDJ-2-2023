
#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <cstdlib>
#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"


class Game {
    private:
        Game(const char* title, int width , int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State* GetState();
        static Game& GetInstance();
};

#endif  // INCLUDE_GAME_H_
