#ifndef INCLUDE_GAMEOBJECT_H_
#define INCLUDE_GAMEOBJECT_H_
#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"

class Component;

class GameObject {
    public:
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(const char* type);
        Rect box;
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
};

#endif  // INCLUDE_GAMEOBJECT_H_
