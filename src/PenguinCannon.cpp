#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody)
: Component(associated),
    pBody(penguinBody),
    angle(0)
{
    Sprite* penguinCannon = new Sprite(associated,"Recursos/img/cubngun.png");
    penguinBody.lock()->AddComponent(penguinCannon);
}

void PenguinCannon::Update(float dt) {
    InputManager& im = InputManager::GetInstance();
    if (pBody.lock() != nullptr) {
        associated.box.SetCenter(pBody.lock()->box.GetCenter());
        Vec2 dist = Vec2::DistEntreDoisPontos(associated.box.GetCenter(),Vec2(im.GetMouseX(),im.GetMouseY()) + Camera::pos);
        associated.angleDeg = dist.GetAngleDeg();
    } else {
        associated.RequestDelete();
    }

    if (im.MousePress(SDL_BUTTON_LEFT)) {
        Shoot();
    }
}

void PenguinCannon::Start() {}

void PenguinCannon::Render() {}

void PenguinCannon::Shoot() {
    int damage = std::rand() % 10 + 10;


    GameObject* bulletGO = new GameObject();
    Bullet* bullet = new Bullet(
                                (*bulletGO),
                                associated.angleDeg * M_PI / 180,
                                CANNON_BULLET_SPEED,
                                damage,
                                associated.box.GetCenter().DistToOrigin(),
                                "Recursos/img/penguinbullet.png",
                                CANNON_BULLET_COUNT,
                                0.15
                                );
    bulletGO->AddComponent(bullet);

    int cannonBulletWidth = ((Sprite*) bulletGO->GetComponent("Sprite"))->GetWidth();

    Vec2 posBulletCannon = associated.box.GetCenter() + Vec2(associated.box.w / 2, ZERO);


    bulletGO->box.SetCenter(posBulletCannon);

    Game::GetInstance().GetState()->AddObject(bulletGO);
}

bool PenguinCannon::Is(std::string type) {
    return type == "PenguinCannon";
}