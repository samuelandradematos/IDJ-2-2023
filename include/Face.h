#ifndef INCLUDE_FACE_H_
#define INCLUDE_FACE_H_
#include "GameObject.h"
#include <string>
#include "InputManager.h"
#include "Camera.h"

class GameObject;
class Face : public Component {
    public:
        Face(GameObject& associated);  // NOLINT
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
    private:
        int hitpoints;
};

#endif  // INCLUDE_FACE_H_
