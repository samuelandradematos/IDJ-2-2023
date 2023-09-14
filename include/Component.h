#ifndef INCLUDE_COMPONENT_H_
#define INCLUDE_COMPONENT_H_
#include "GameObject.h"

class GameObject;

class Component {
    public:
        explicit Component(GameObject& ass);  // NOLINT
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(const char* type) = 0;
    protected:
        GameObject& associated;
};

#endif  // INCLUDE_COMPONENT_H_
