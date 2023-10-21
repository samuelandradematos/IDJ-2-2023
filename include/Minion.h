#ifndef INCLUDE_MINION_H_
#define INCLUDE_MINION_H_
#include "Component.h"
#include <memory>
#include "Vec2.h"
#include "Sprite.h"
#include <cmath>
#include "Bullet.h"
#include "Game.h"

#define MINION_ANGULARSPEED -45
#define MINION_BULLETSPEED 150
#define MINION_BULLETDMG 30
#define DIST_INICIAL 150
#define MAX_SCALE 150
#define MIN_SCALE 100

class Minion : public Component {
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
        void Start();
    private:
        std::weak_ptr<GameObject> alienCtr;
        float arc;
};

#endif //INCLUDE_MINION_H_
