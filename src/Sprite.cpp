#include <iostream>
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"


Sprite::Sprite(GameObject& associated): Component(associated), scale({1,1}), texture(nullptr), started(false) {}

Sprite::Sprite(GameObject& associated, const std::string& file) : Component(associated), scale({1,1}), texture(nullptr), started(false) {
    Open(file);
    associated.box.h = (float)height;
    associated.box.w = (float)width;
    std::cout << "Inializou o arquivo: |" << file << "|"<< std::endl;
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

    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render() {
    Render((int)associated.box.x, (int)associated.box.y);
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect = {x - (int)Camera::pos.x, y - (int)Camera::pos.y, (int)associated.box.w, (int)associated.box.h};
    int RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);

    if (RENDER_ERROR != 0) {
        std::cout << "Texture render failure: " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetHeight() {
    return height * scale.x;
}

int Sprite::GetWidth() {
    return width * scale.y;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) {
        std::cout << "Box.w: " << associated.box.w << std::endl;
        scale.x = scaleX;
        associated.box.w = associated.box.w * scale.x;
        std::cout << "Depois da scala Box.w: " << associated.box.w << std::endl;
    }

    if (scaleY != 0) {
        std::cout << "Box.h: " << associated.box.h << std::endl;
        scale.y = scaleY;
        associated.box.h = associated.box.h * scale.y;
        std::cout << "Box.h: " << associated.box.h << std::endl;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::Update(float dt) {}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::Start() {}
