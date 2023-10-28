#ifndef INCLUDE_PENGUINBODY_H_
#define INCLUDE_PENGUINBODY_H_
#include "Component.h"
#include "memory"
#include "Vec2.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "State.h"
#define BODY_ACCELERATION 75
#define BODY_MAX_SPEED 300
#define BODY_MIN_SPEED -300
#define BODY_ANGULAR_SPEED 100

class PenguinBody : public Component {
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        PenguinBody* player;
    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed, angle;
        int hp;
};

#endif //INCLUDE_PENGUINBODY_H_
