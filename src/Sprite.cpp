#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(const GameObject& associated): Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(const GameObject& associated, const char* file) {
    texture = nullptr;
    Open(file);
    associated.box.h = height;
    associated.box.w = width;
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::Open(const char* file) {
    Game& jogo = Game::GetInstance();
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = IMG_LoadTexture(jogo.GetRenderer(), file);
        if (texture == nullptr) {
            std::cout << SDL_GetError() << std::endl;
            return;
        }
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }

    texture = IMG_LoadTexture(jogo.GetRenderer(), file);
    if (texture == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
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
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetHeight() {
    return height;
}

int Sprite::GetWidth() {
    return width;
}

bool Sprite::IsOpen() {
    if (texture != nullptr)
        return true;
    else
        return false;
}

void Sprite::Update(float dt) {
}

void Sprite::Render() {
}

bool Sprite::Is(const char* type) {
    return type == "Sprite";
}
