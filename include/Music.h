#ifndef MUSIC_H_
#define MUSIC_H_
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {
    public:
        Music();
        ~Music();
        Music(const char* file);
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(const char* file);
        bool IsOpen();
    private:
        Mix_Music* music;
};


#endif  // MUSIC_H_
