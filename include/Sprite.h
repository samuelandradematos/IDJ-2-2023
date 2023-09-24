#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_
#include <string>
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"


class Sprite: public Component {
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, const std::string& file);
        ~Sprite();
        void Open(const std::string& file);
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        void Render();
        void Render(int x,int y);
        bool Is(std::string type);
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};
#endif  // INCLUDE_SPRITE_H_
