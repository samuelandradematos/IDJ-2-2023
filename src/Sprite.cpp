#include <iostream>
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"


Sprite::Sprite(GameObject& associated): Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, const std::string& file) : Component(associated) {
    texture = nullptr;
    Open(file);
    associated.box.h = (float)height;
    associated.box.w = (float)width;
}

Sprite::~Sprite() {
}

void Sprite::Open(const std::string& file) {
    Game& game = Game::GetInstance();
    if (texture != nullptr) {
        texture = Resources::GetImage(file);
        if (texture != nullptr)
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }

    texture = Resources::GetImage(file);
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

void Sprite::Render() {
    Render((int)associated.box.x, (int)associated.box.y);
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect;
    dstRect.x = x - Camera::pos.x;
    dstRect.y = y - Camera::pos.y;
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
    return texture != nullptr;
}

void Sprite::Update(float dt) {
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}
