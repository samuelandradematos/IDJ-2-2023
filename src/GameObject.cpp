#include <iostream>
#include <typeinfo>
#include <SDL.h>
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
    for (const auto & component : components) {
        component->Render();
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
    for (auto i = components.begin(); i < components.end(); i++) {
        if (cpt == (Component *) (*i).get()) {
            components.erase(i);
        }
    }
}

Component* GameObject::GetComponent(const std::string& type) {
    std::cout << "GameObject::GetComponent com valor: " << type << std::endl;
    for (const auto & component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}
