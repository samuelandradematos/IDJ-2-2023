#ifndef MUSIC_H_
#define MUSIC_H_
#include <string>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {
    public:
        Music();
        ~Music();
        Music(const std::string& file);
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(const std::string& file);
        bool IsOpen();
    private:
        Mix_Music* music;
};


#endif  // MUSIC_H_
