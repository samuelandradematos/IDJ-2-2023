#include "Text.h"
#include "Resources.h"
#include "GameObject.h"
#include "Camera.h"
#include "Game.h"

Text::Text(
    GameObject &associatedGO,
    std::string fontFile,
    int fontSize,
    Text::TextStyle style,
    std::string text,
    SDL_Color color,
    float blinkInterval) :
    Component(associatedGO),
    texture(nullptr),
    text(text),
    style(style),
    fontFile(fontFile),
    fontSize(fontSize),
    color(color),
    blinkInterval(blinkInterval)
{

    font = Resources::GetFont(fontFile,fontSize);
    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    #ifdef DEBUG
        std::cout << "~Text(): " << text << std::endl;
    #endif // DEBUG
}

void Text::Update(float dt) {
    if (blinkInterval != 0) {
        blinkTimer.Update(dt);
        if (blinkTimer.Get() >= blinkInterval) {
            colorBefore = color;
            SetColor(INV);
            blinkTimer.Restart();
        }
        if (IsColorEqual(color,INV) && blinkTimer.Get() >= blinkInterval) {
            SetColor(colorBefore);
            blinkTimer.Restart();
        }
    }
}

void Text::Render() {
    if (texture != nullptr) {
        SDL_Rect clipRect = {0,0,(int)associated.box.w, (int)associated.box.h};
        SDL_Rect dstRect = {(int)(associated.box.x - Camera::pos.x),(int)(associated.box.y - Camera::pos.y),clipRect.w,clipRect.h};

        int RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstRect,associated.angleDeg,
                                            nullptr, SDL_FLIP_NONE);
        if (RENDER_ERROR != 0) {
            std::cout << "Text render: " << SDL_GetError() << std::endl;
        }
    }
}

void Text::SetText(std::string newText) {
    text = newText;
    RemakeTexture();
}

void Text::SetStyle(Text::TextStyle newStyle) {
    style = newStyle;
    RemakeTexture();
}

void Text::SetFontSize(int newFontSize) {
    fontSize = newFontSize;
    RemakeTexture();
}

void Text::SetFontFile(std::string newFontFile) {
    fontFile = newFontFile;
    RemakeTexture();
}

void Text::SetColor(SDL_Color newColor) {
    color = newColor;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    font = Resources::GetFont(fontFile,fontSize);
    if (font != nullptr) {
        switch (style) {
            case SOLID:
            {
                SDL_Surface* auxSurface = TTF_RenderUTF8_Solid(font,text.c_str(),color);
                if (auxSurface == nullptr) {
                    std::cout << SDL_GetError() << std::endl;
                    break;
                }
                texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),auxSurface);
                if (texture == nullptr) {
                    std::cout << SDL_GetError() << std::endl;
                    break;
                } else {
                    associated.box.w = auxSurface->w;
                    associated.box.h = auxSurface->h;
                }
                SDL_FreeSurface(auxSurface);
                break;
            }
            case SHADED:
            {
                SDL_Surface* auxSurface = TTF_RenderUTF8_Shaded(font,text.c_str(),color,BG);
                if (auxSurface == nullptr) {
                    std::cout << SDL_GetError() << std::endl;
                    break;
                }
                texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),auxSurface);
                if (texture == nullptr) {
                    std::cout << SDL_GetError() << std::endl;
                    break;
                } else {
                    associated.box.w = auxSurface->w;
                    associated.box.h = auxSurface->h;
                }
                SDL_FreeSurface(auxSurface);
                break;
            }
            case BLENDED:
            {
                SDL_Surface* auxSurface = TTF_RenderUTF8_Blended(font,text.c_str(),color);
                if (auxSurface == nullptr) {
                    std::cout << SDL_GetError() << std::endl;
                    break;
                }
                texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),auxSurface);
                if (texture == nullptr) {
                    std::cout << SDL_GetError() << std::endl;
                    break;
                } else {
                    associated.box.w = auxSurface->w;
                    associated.box.h = auxSurface->h;
                }
                SDL_FreeSurface(auxSurface);
                break;
            }
        }
    }
}

bool Text::Is(std::string type) {
    return type == "Text";
}

bool Text::IsColorEqual(SDL_Color fstColor, SDL_Color sndColor) {
    return fstColor.r == sndColor.r && fstColor.g == sndColor.g && fstColor.b == sndColor.b && fstColor.a == sndColor.a;
}
