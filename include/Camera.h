
#ifndef INCLUDE_CAMERA_H_
#define INCLUDE_CAMERA_H_
#include "GameObject.h"
#include "InputManager.h"
#include <iostream>

class Camera {
    public:
        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);
        static Vec2 pos;
        static Vec2 speed;
    private:
        static GameObject* focus;
};


#endif  // INCLUDE_CAMERA_H_
