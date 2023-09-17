#ifndef INCLUDE_SOUND_H_
#define INCLUDE_SOUND_H_
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"
#include <string>

class GameObject;

class Sound : public Component {
    public:
        Sound(GameObject& associated);  // NOLINT
        Sound(GameObject& associated, const std::string& file);  // NOLINT
        ~Sound();
        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
    private:
        Mix_Chunk* chunk;
        int channel;
};


#endif  // INCLUDE_SOUND_H_
