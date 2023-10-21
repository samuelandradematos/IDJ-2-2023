
#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"

class State;

class Game {
    private:
        Game(std::string title, int width , int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        int frameStart;
        float dt;
        void CalculateDeltaTime();
        float GetDeltaTime();

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State* GetState();
        static Game& GetInstance();
};

#endif  // INCLUDE_GAME_H_
