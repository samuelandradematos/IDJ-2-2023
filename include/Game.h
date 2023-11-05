
#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <stack>
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"
#include "StageState.h"

class State;

class Game {
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        static Game& GetInstance();
        State& GetCurrentState();
        void Push(State* state);
        float GetDeltaTime();
        Vec2 GetWindowCenter();
    private:
        Game(std::string title, int width , int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* storedState;
        int frameStart;
        float dt;
        std::stack<std::unique_ptr<State>> stateStack;
        void CalculateDeltaTime();
};

#endif  // INCLUDE_GAME_H_
