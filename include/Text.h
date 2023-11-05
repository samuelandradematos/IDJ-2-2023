#ifndef INCLUDE_TEXT_H_
#define INCLUDE_TEXT_H_
#include "Component.h"
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Timer.h"

const static SDL_Color INV = {0, 0, 0, 0};
const static SDL_Color BG = {0,0,0,255};
const static SDL_Color BLUE = {51,51,204,255};
const static SDL_Color GREEN = {51,204,51,255};
const static SDL_Color CYAN = {0,204,255,255};
const static SDL_Color PURPLE = {204,0,255,255};
const static SDL_Color REDISH = {179,0,0,255};
const static SDL_Color RED = {255,0,0,255};
const static SDL_Color WHITE = {255,255,255,255};

class Text : public Component {
    public:
        enum TextStyle {SOLID, SHADED, BLENDED};
        Text(GameObject& associatedGO, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float blinkInterval = 0);
        ~Text();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void SetText(std::string newText);
        void SetColor(SDL_Color newColor);
        void SetStyle(TextStyle newStyle);
        void SetFontFile(std::string newFontFile);
        void SetFontSize(int newFontSize);
    private:
        void RemakeTexture();
        TTF_Font* font;
        SDL_Texture* texture;
        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;
        float blinkInterval;
        Timer blinkTimer;
        SDL_Color colorBefore;
        bool IsColorEqual(SDL_Color fstColor, SDL_Color sndColor);
};

#endif //INCLUDE_TEXT_H_
