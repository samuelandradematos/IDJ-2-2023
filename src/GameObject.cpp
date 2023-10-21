#include <iostream>
#include <typeinfo>
#include <SDL.h>
#include "GameObject.h"

GameObject::GameObject() : angleDeg(0), started(false), isDead(false) {}

GameObject::~GameObject() {
    components.clear();
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
    for (const auto & it : components){
        it->Start();
    }
    started = true;
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
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
