#include "Face.h"

Face::Face(GameObject& ass) : Component(associated) {
    hitpoinst = 30;
}

void Face::Damage(int damage) {
    if (hitpoints <= 0) {
        associated.RequestDelete();
        if (associated.GetComponent("Sound") != nullptr)
            associated.GetComponent("Sound").Play();
    } else {
        hitpoints = hitpoints - damage;
    }
}

void Face::Update(float dt) {}

void Face::Render() {}

bool Face::Is(const char* type) {
    return type == "Face";
}
