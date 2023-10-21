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

void Face::Update(float dt) {
    // Carrega a instancia de input
    InputManager& im = InputManager::GetInstance();

    // Se for um click do botão esquerdo do mouse
    if (im.MousePress(LEFT_MOUSE_BUTTON)) {

        // Se a posição do click está dentro do objeto FACE
        if (associated.box.Contains((float) im.GetMouseX() - Camera::pos.x, (float) im.GetMouseY()) - Camera::pos.y) {
            // Gera o valor do dano
            int damage = std::rand() % 10 + 10;

            // Aplica o dano
            Damage(damage);
        }
    }
}

void Face::Render() {}

void Face::Start() {}

bool Face::Is(std::string type) {
    return type == "Face";
}
