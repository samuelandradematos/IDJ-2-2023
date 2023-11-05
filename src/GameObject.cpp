#include <iostream>
#include "GameObject.h"

GameObject::GameObject() : angleDeg(0), started(false), isDead(false), holdEnd(false) {}

GameObject::~GameObject() {
    components.clear();
    #ifdef DEBUG
        std::cout << "~GameObject()" << std::endl;
    #endif // DEBUG
}

void GameObject::Update(float dt) {
    for (const auto & component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (const auto & component : components) {
        component->Render();
    }
}

void GameObject::Start() {
    for (long long unsigned it = 0; it < components.size(); it++){
        components.at(it)->Start();
    }
    started = true;
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    if (holdEnd) {
        isDead = false;
    } else {
        isDead = true;
    }
}

void GameObject::NotifyCollision(GameObject &other) {
    for (long long unsigned it = 0; it < components.size() ; it++){
        components.at(it)->NotifyCollision(other);
    }
}

void GameObject::AddComponent(Component* cpt) {
    if (started)
        cpt->Start();
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    for (auto i = components.begin(); i < components.end(); i++) {
        if (cpt == (Component*) (*i).get()) {
            components.erase(i);
        }
    }
}

Component* GameObject::GetComponent(const std::string& type) {
    for (const auto & component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}

void GameObject::HoldEnd() {
    holdEnd = true;
}

bool GameObject::IsHoldingEnd() {
    return holdEnd;
}

void GameObject::ReleaseEnd() {
    holdEnd = false;
}
