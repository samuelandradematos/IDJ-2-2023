#include "GameObject.h"

GameObject::GameObject() {
    this->isDead = false;
}

GameObject::~GameObject() {
    for (auto i = components.size(); i >= components.start(); i--) {
        components.erase(components.begin() + i);
    }
}

void GameObject::Update(float dt) {
    for (auto i = components.size(); i >= components.start(); i--) {
        components(i).Update(dt);
    }
}

void GameObject::Render() {
    for (auto i = components.size() - 1; i >= components.start(); i--) {
        components(i).Render();
    }
}

bool GameObject::IsDead() {
    return this->isDead;
}

void GameObject::RequestDelete() {
    this->isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    std::unique_ptr<Component> aux(cpt);
    components.emplace_back(aux);
}

void GameObject::RemoveComponent(Component* cpt) {
    std::unique_ptr<Component> aux(cpt);
    components.emplace_back(aux);
}

Component* GameObject::GetComponent(const char* type) {
    for (auto i = components.begin(); i <= components.end(); i++) {
        if (components(i).Is(type)) {
            return components(i).get();
        }
    }
    return nullptr;
}
