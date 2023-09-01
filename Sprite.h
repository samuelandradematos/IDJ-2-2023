#ifndef SPRITE_H_
#define SPRITE_H_
#define INCLUDE_SDL_IMAGE
#include "src/include/SDL2/SDL_include.h"
#endif  // SPRITE_H_

class Sprite {
    public:
        Sprite();
        explicit Sprite(const char* file);
        ~Sprite();
        void Open(const char* file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
    private:
        SDL_Texture* texture;
        int widht;
        int height;
        SDL_Rect clipRect;
};
