#ifndef INCLUDE_BULLET_H_
#define INCLUDE_BULLET_H_
#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include <cmath>

class Bullet : public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
    public:
        Bullet(GameObject& associated, float angle, float newSpeed, int newDamage, float maxDistance, std::string sprite);
        void Update(float dt);
        void Render();
        void Start();
        bool Is(std::string type);
        int GetDamage();
};

#endif //INCLUDE_BULLET_H_
