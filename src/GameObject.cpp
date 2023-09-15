#include "GameObject.h"

GameObject::GameObject() {
    this->isDead = false;
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto i = components.begin(); i < components.end(); i++) {
        (*i)->Update(dt);
    }
}

void GameObject::Render() {
    for (auto i = components.end() - 1; i >= components.begin(); i--) {
        (*i)->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    components.emplace_back(cpt);
}

Component* GameObject::GetComponent(const char* type) {
    for (auto i = components.begin(); i <= components.end(); i++) {
        if ((*i)->Is(type)) {
            return (*i).get();
        }
    }
    return nullptr;
}
