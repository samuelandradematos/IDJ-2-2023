#include "PenguinCannon.h"
#include "Collider.h"
#include "InputManager.h"
#include "Camera.h"
#include "PenguinBody.h"

PenguinCannon::PenguinCannon(GameObject &assGO, std::weak_ptr<GameObject> penguinBody)
: Component(assGO),
    pBody(penguinBody),
    angle(0)
{
    Sprite* penguinCannon = new Sprite(associated, "Recursos/img/cubngun.png");
    associated.AddComponent(penguinCannon);

    associated.box.SetCenter(pBody.lock()->box.GetCenter());

    Collider* pcCollider = new Collider(associated);
    associated.AddComponent(pcCollider);
}

void PenguinCannon::Update(float dt) {

    shootCooldown.Update(dt);

    if (pBody.lock() != nullptr) {
        associated.box.SetCenter(pBody.lock()->box.GetCenter());
        Vec2 mousePos = Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
        Vec2 rotation = (associated.box.GetCenter() - mousePos) - Camera::pos;
        rotation.Rotate(M_PI);
        associated.angleDeg = rotation.GetAngleDeg();
    } else {
        associated.RequestDelete();
    }

    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
        Shoot();
    }
}

void PenguinCannon::NotifyCollision(GameObject &other) {
    if (other.GetComponent("Bullet") != nullptr) {
        Bullet* bullet = ((Bullet *) (other.GetComponent("Bullet")));
        if (bullet->targetsPlayer) {
            static int count = 1;
            std::cout << "PenguinCannon collision notified: " << count << std::endl;
            count++;
        }
        if (bullet->targetsPlayer && bullet->GetDistanceLeft() <= BULLET_MIN_DIST) {
            PenguinBody *penguinBodyPtr = (PenguinBody *) (pBody.lock()->GetComponent("PenguinBody"));
            int damage = bullet->GetDamage();
            penguinBodyPtr->TakeDamage(damage);
        }
    }
}

void PenguinCannon::Start() {}

void PenguinCannon::Render() {
#ifdef DEBUG
    Vec2 center( associated.box.GetCenter() );
    SDL_Point points[5];

    Vec2 point = (Vec2(associated.box.x, associated.box.y) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
                 + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(associated.box.x + associated.box.w, associated.box.y) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
            + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
            + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(associated.box.x, associated.box.y + associated.box.h) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
            + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}


void PenguinCannon::Shoot() {
    int damage = std::rand() % 10 + 10;

    if (shootCooldown.Get() >= CANNON_SHOOT_CDW) {

        GameObject *bulletGO = new GameObject();
        Bullet *bullet = new Bullet(
                (*bulletGO),
                associated.angleDeg * M_PI / 180,
                CANNON_BULLET_SPEED,
                damage,
                associated.box.GetCenter().DistToOrigin(),
                "Recursos/img/penguinbullet.png",
                CANNON_BULLET_COUNT,
                0.25,
                0,
                false,
                true,
                false
        );
        bulletGO->AddComponent(bullet);

        // Conta errada não leva em consideração a inclinação (e deve levar pois o canhão pode estar rotaciaonado de qlq angulo).

        Vec2 posBulletCannon;

        posBulletCannon.DefPosByDistanceToObjCentered(associated.box.GetCenter(),associated.box.w / 2,associated.angleDeg * DEGREE_TO_RAD, 0,0);

        bulletGO->box.SetCenter(posBulletCannon);

        Game::GetInstance().GetCurrentState().AddObject(bulletGO);

        shootCooldown.Restart();
    }
}

bool PenguinCannon::Is(std::string type) {
    return type == "PenguinCannon";
}