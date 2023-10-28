#include "PenguinBody.h"

PenguinBody::PenguinBody(GameObject &associated)
: Component(associated),
    speed({1,1}),
    linearSpeed(0),
    angle(0),
    hp(30)
{
    Sprite* penguinBody = new Sprite(associated, "Recursos/img/penguin.png");
    associated.AddComponent(penguinBody);

    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    auto pcGO = new GameObject();
    PenguinCannon* pc = new PenguinCannon(*pcGO,Game::GetInstance().GetState()->GetObjectPtr(&associated));
    pcGO->AddComponent(pc);
    pcannon = Game::GetInstance().GetState()->AddObject(pcGO);
}

void PenguinBody::Update(float dt) {
    InputManager& im = InputManager::GetInstance();

    if (im.KeyPress(SDLK_w)) {
        // Verifies if x speed is higher than max speed
        if (speed.x < BODY_MAX_SPEED) {
            speed.x += BODY_ACCELERATION * dt;
        } else {
            speed.x = BODY_MAX_SPEED;
        }

        // Verifies if y speed is higher than max speed
        if (speed.y < BODY_MAX_SPEED) {
            speed.y += BODY_ACCELERATION + dt;
        } else {
            speed.y = BODY_MAX_SPEED;
        }
    }

    if (im.KeyPress(SDLK_s)) {
        // Verifies if x speed is lower than min speed
        if (speed.x > BODY_MIN_SPEED) {
            speed.x -= BODY_ACCELERATION * dt;
        } else {
            speed.x = BODY_MIN_SPEED;
        }

        // Verifies if y speed is lower than min speed
        if (speed.y > BODY_MIN_SPEED) {
            speed.y -= BODY_ACCELERATION + dt;
        } else {
            speed.y = BODY_MIN_SPEED;
        }
    }

    if (im.KeyPress(SDLK_a)) {
        angle = atan2(associated.box.y, associated.box.x);
        angle -= BODY_ANGULAR_SPEED * dt;
    }

    if (im.KeyPress(SDLK_d)) {
        angle = atan2(associated.box.y, associated.box.x);
        angle += BODY_ANGULAR_SPEED * dt;
    }

    associated.angleDeg += angle * 180 / M_PI;

    associated.box.x += speed.x;
    associated.box.y += speed.y;


    if (hp <= 0) {
        pcannon.lock()->RequestDelete();
        associated.RequestDelete();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(std::string type) {
    return type == "PenguinBody";
}
