#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_
#include <string>
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#define ZERO 0


class Sprite: public Component {
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, const std::string& file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
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
        void Start();
        void SetScale(float scaleX, float scaleY);
        Vec2 GetScale();
        void SetFrame(int newFrame);
        void SetFrameCount(int newFrameCount);
        void SetFrameTime(float newFrameTime);
    private:
        float secondsToSelfDestruct;
        Timer selfDestructCount;
        int frameCount, currentFrame;
        float timeElapsed, frameTime;
        Vec2 scale;
        float angle;
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
        bool started;
};
#endif  // INCLUDE_SPRITE_H_
