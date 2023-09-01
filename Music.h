#ifndef MUSIC_H_
#define MUSIC_H_
#define INCLUDE_SDL_MIXER
#include <string>
#include "src/include/SDL2/SDL_include.h"
#endif  // MUSIC_H_

class Music {
    public:
        Music();
        explicit Music(string file);
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file);
        bool IsOpen();
    private:
        Mix_Music* music;
};


