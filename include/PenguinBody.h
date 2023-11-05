#ifndef INCLUDE_PENGUINBODY_H_
#define INCLUDE_PENGUINBODY_H_
#include "Component.h"
#include "memory"
#include "Vec2.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "StageState.h"
#define BODY_ACCELERATION 10
#define BODY_MAX_SPEED 40
#define BODY_MIN_SPEED -40
#define BODY_ANGULAR_SPEED 5
#define PENGUIN_DEATH_FRAME_TIME 10
#define PENGUIN_DEATH_FRAME_COUNT 4
#define PENGUIN_HP 30


class PenguinBody : public Component {
    public:
        PenguinBody(GameObject& assGO);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        Vec2 GetPlayerCenteredPos();
        static PenguinBody* player;
        void NotifyCollision(GameObject& other);
        void TakeDamage(int damage);
        bool IsDead();
    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed, angle;
        int hp;
};

#endif //INCLUDE_PENGUINBODY_H_
