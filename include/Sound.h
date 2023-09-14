#ifndef INCLUDE_SOUND_H_
#define INCLUDE_SOUND_H_
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"

class GameObject;

class Sound : public Component {
    public:
        explicit Sound(const GameObject& associated);
        Sound(const GameObject& associated, const char* file);
        ~Sound();
        void Play(int times = 1);
        void Stop();
        void Open(const char* file);
        bool IsOpen();
        void Update(float dt);
        void Render();
        void Is(const char* type);
    private:
        Mix_Chunk* chunk;
        int channel;
};


#endif  // INCLUDE_SOUND_H_
