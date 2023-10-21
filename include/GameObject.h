#ifndef INCLUDE_GAMEOBJECT_H_
#define INCLUDE_GAMEOBJECT_H_
#include <vector>
#include <string>
#include <memory>
#include "Component.h"
#include "Rect.h"

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
        void Start();
        Component* GetComponent(const std::string& type);
        Rect box;
        double angleDeg;
        bool started;
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
};

#endif  // INCLUDE_GAMEOBJECT_H_
