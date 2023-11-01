#include "Camera.h"
#include "Game.h"
#define CAMERA_SPEED 200

Vec2 Camera::speed;
Vec2 Camera::pos;

GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus == nullptr) {
        InputManager& im = InputManager::GetInstance();

        // Altera os valores em Y
        if (im.IsKeyDown(UP_ARROW_KEY)) {
            std::cout << "UP arrow key" << std::endl;
            speed.y = 0 - CAMERA_SPEED;
        } else if (im.IsKeyDown(DOWN_ARROW_KEY)) {
            std::cout << "DOWN arrow key" << std::endl;
            speed.y = 0 + CAMERA_SPEED;
        } else {
            speed.y = 0;
        }

        // Altera os valores em X
        if (im.IsKeyDown(LEFT_ARROW_KEY)) {
            std::cout << "Left arrow key" << std::endl;
            speed.x = 0 - CAMERA_SPEED;
        } else if (im.IsKeyDown(RIGHT_ARROW_KEY)) {
            std::cout << "Right arrow key" << std::endl;
            speed.x = 0 + CAMERA_SPEED;
        } else {
            speed.x = 0;
        }

        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    } else {
        int w,h;
        if (!SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(),&w,&h)){
        } else {
            std::cout << "Error on getting RenderInfo: " << SDL_GetError() << std::endl;
        }
        pos.x = focus->box.GetCenter().x - w / 2;
        pos.y = focus->box.GetCenter().y - h / 2;
    }
}

