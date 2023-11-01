#include <iostream>
#include "Sprite.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"


Sprite::Sprite(GameObject& associated): Component(associated), scale({1,1}), texture(nullptr), started(false) {}

Sprite::Sprite(GameObject& associated, const std::string& file, int frameCount, float frameTime, float secondsToSelfDestruct)
: Component(associated),
    secondsToSelfDestruct(secondsToSelfDestruct),
    frameCount(frameCount),
    currentFrame(0),
    timeElapsed(0.0),
    frameTime(frameTime),
    scale({1,1}),
    texture(nullptr),
    started(false)
{
    Open(file);
    std::cout << "Loaded Sprite: |" << file << "|" << std::endl;
}

Sprite::~Sprite() {}

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
    SetClip(0, 0, width/frameCount, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    associated.box.w = w * scale.x;
    associated.box.h = h * scale.y;
}

void Sprite::Render() {
    Render((int)associated.box.x, (int)associated.box.y);
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect = {x - (int)Camera::pos.x, y - (int)Camera::pos.y, (int)(clipRect.w * GetScale().x), (int)(clipRect.h * GetScale().y)};
    int RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);

    if (RENDER_ERROR != 0) {
        std::cout << "Texture render failure: " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetHeight() {
    return height * scale.x;
}

int Sprite::GetWidth() {
    return (width * scale.y) / frameCount;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) {
        scale.x = scaleX;
        associated.box.w = associated.box.w * scale.x;
    }

    if (scaleY != 0) {
        scale.y = scaleY;
        associated.box.h = associated.box.h * scale.y;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::Update(float dt) {
    timeElapsed += dt;

    if (secondsToSelfDestruct > 0) {
        selfDestructCount.Update(dt);
        if (selfDestructCount.Get() > secondsToSelfDestruct) {
            associated.RequestDelete();
        } else if (timeElapsed >= frameTime) {
            currentFrame = (currentFrame + 1) % frameCount;

            SetFrame(currentFrame);
            timeElapsed = 0;
        }
    } else if (timeElapsed >= frameTime) {
        currentFrame = (currentFrame + 1) % frameCount;

        SetFrame(currentFrame);
        timeElapsed = 0;
    }
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::Start() {}

void Sprite::SetFrame(int newFrame) {
    currentFrame = newFrame;
    SetClip(currentFrame * (GetWidth() / scale.x),ZERO, GetWidth() / scale.x, GetHeight() / scale.y);
}

void Sprite::SetFrameCount(int newFrameCount) {
    frameCount = newFrameCount;
}

void Sprite::SetFrameTime(float newFrameTime) {
    frameTime = newFrameTime;
}


