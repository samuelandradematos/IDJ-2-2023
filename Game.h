
#ifndef GAME_H_
#define GAME_H_
#include <string>
#include <cstdlib>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "src/include/SDL2/SDL_include.h"
#include "State.h"
#endif  // GAME_H_

namespace std {
class Game {
    private:
        Game(string title, int width , int height);
        Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State* GetState();
        Game& GetInstance();
};
};  // namespace std

