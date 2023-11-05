#ifndef INCLUDE_COLLIDER_H_
#define INCLUDE_COLLIDER_H_
#include "Component.h"
#include "Rect.h"
#include <algorithm>
#include <cmath>


class Collider : public Component {
    public:
        Collider(GameObject& assGO, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void SetScale(Vec2 scaleNew);
        void SetOffset(Vec2 offsetNew);
        Rect box;
        void NotifyCollision(GameObject& other);
        static bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB);
    private:
        Vec2 scale;
        Vec2 offset;
};

#endif //INCLUDE_COLLIDER_H_
