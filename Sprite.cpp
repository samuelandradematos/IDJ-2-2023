#include "Sprite.h"
#include "Game.h"

namespace std {

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(const char* file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::Open(const char* file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = IMG_LoadTexture(GetRenderer(), file);
        if (texture = nullptr) {
            SDL_GetError();
            return;
        }
        SDL_QueryTexture(texture, nullptr, nullptr, &widht, &height);
    } else {
        texture = IMG_LoadTexture(GetRenderer(), file);
        if (texture = nullptr) {
            SDL_GetError();
            return;
        }
        SDL_QueryTexture(texture, nullptr, nullptr, &widht, &height);
    }
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    SDL_RenderCopy(GetRenderer(), texture, clipRect, dstRect);
}

int Sprite::GetHeight() {
    return height;
}

int Sprite::GetWidth() {
    return widht;
}

bool Sprite::IsOpen() {
    if (texture != nullptr)
        return true;
    else
        return false;
}


}  // namespace std
