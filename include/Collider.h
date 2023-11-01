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

    static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
        Vec2 A[] = { Vec2( a.x, a.y + a.h ),
                     Vec2( a.x + a.w, a.y + a.h ),
                     Vec2( a.x + a.w, a.y ),
                     Vec2( a.x, a.y )
        };
        Vec2 B[] = { Vec2( b.x, b.y + b.h ),
                     Vec2( b.x + b.w, b.y + b.h ),
                     Vec2( b.x + b.w, b.y ),
                     Vec2( b.x, b.y )
        };

        for (auto& v : A) {
            v = (v - a.GetCenter()).RotateVec(angleOfA) + a.GetCenter();
        }

        for (auto& v : B) {
            v = (v - b.GetCenter()).RotateVec(angleOfB) + b.GetCenter();
        }

        Vec2 axes[] = { (A[0] - A[1]).NormalizeVec(), (A[1] - A[2]).NormalizeVec(), (B[0] - B[1]).NormalizeVec(), (B[1] - B[2]).NormalizeVec() };

        for (auto& axis : axes) {
            float P[4];

            for (int i = 0; i < 4; ++i) P[i] = A[i].DotProduct(axis);

            float minA = *std::min_element(P, P + 4);
            float maxA = *std::max_element(P, P + 4);

            for (int i = 0; i < 4; ++i) P[i] = B[i].DotProduct(axis);

            float minB = *std::min_element(P, P + 4);
            float maxB = *std::max_element(P, P + 4);

            if (maxA < minB || minA > maxB)
                return false;
        }

        return true;
    }

    private:
        Vec2 scale;
        Vec2 offset;
};

#endif //INCLUDE_COLLIDER_H_
