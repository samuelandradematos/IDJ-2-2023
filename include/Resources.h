
#ifndef INCLUDE_RESOURCES_H_
#define INCLUDE_RESOURCES_H_
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "string"
#include "unordered_map"

class Resources {
    public:
        static SDL_Texture* GetImage(std::string file);
        static void ClearImages();
        static Mix_Music* GetMusic(std::string file);
        static void ClearMusics();
        static Mix_Chunk* GetSound(std::string file);
        static void ClearSounds();
        static TTF_Font* GetFont(std::string file, int pointSize);
        static void ClearFonts();
    private:
        static std::unordered_map<std::string, SDL_Texture*> imageTable;
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
        static std::unordered_map<std::string, TTF_Font*> fontTable;
};


#endif  // INCLUDE_RESOURCES_H_
