
#ifndef INCLUDE_PENGUINCANNON_H_
#define INCLUDE_PENGUINCANNON_H_
#include "memory"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

#define MINION_ANGULARSPEED -45
#define CANNON_BULLET_SPEED 150
#define DIST_INICIAL 150
#define CANNON_BULLET_COUNT 4

class PenguinCannon : public Component {
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        void Update(float dt);
        void Render();
        void Start();
        bool Is(std::string type);
        void Shoot();
    private:
        std::weak_ptr<GameObject> pBody;
        float angle;
};

#endif //INCLUDE_PENGUINCANNON_H_
