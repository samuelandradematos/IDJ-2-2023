#include "Camera.h"
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
            speed.y = 0 - CAMERA_SPEED;
        } else if (im.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y = 0 + CAMERA_SPEED;
        } else {
            speed.y = 0;
        }

        // Altera os valores em X
        if (im.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x = 0 - CAMERA_SPEED;
        } else if (im.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = 0 + CAMERA_SPEED;
        } else {
            speed.x = 0;
        }

        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
        std::cout << "X Camera: " << pos.x << std::endl;
        std::cout << "Y Camera: " << pos.y << std::endl;
    } else {

    }
}

