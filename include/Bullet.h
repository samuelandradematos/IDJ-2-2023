#ifndef INCLUDE_BULLET_H_
#define INCLUDE_BULLET_H_
#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include <cmath>
#define BULLET_MIN_DIST 30


class Bullet : public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
    public:
        bool targetsPlayer;
        bool targetsEnemy;
        Bullet(
                GameObject& assGO,
                float angle,
                float newSpeed,
                int newDamage,
                float maxDistance,
                std::string sprite,
                int frameCount,
                float frameTime,
                float secondsToSelfDestruct = 0,
                bool targetIsPlayer = false,
                bool targetIsEnemy = false,
                bool loopAnimation = true
                );
        void Update(float dt);
        void Render();
        void Start();
        bool Is(std::string type);
        int GetDamage();
        void NotifyCollision(GameObject& other);
        float GetDistanceLeft();
};

#endif //INCLUDE_BULLET_H_
