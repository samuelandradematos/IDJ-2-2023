#ifndef INCLUDE_FACE_H_
#define INCLUDE_FACE_H_
#include "GameObject.h"

class Face : public Component {
    public:
        explicit Face(GambeObject& associated);  // NOLINT
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(const char* type);
    private:
        int hitpoints;
};

#endif  // INCLUDE_FACE_H_
