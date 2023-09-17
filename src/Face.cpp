#include <iostream>
#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    if (hitpoints <= 0) {
        associated.RequestDelete();
        if (associated.GetComponent("Sound") != nullptr)
            ((Sound*)associated.GetComponent("Sound"))->Play();
    } else {
        hitpoints = hitpoints - damage;
    }
}

void Face::Update(float dt) {}

void Face::Render() {
}

bool Face::Is(std::string type) {
    return type == "Face";
}
