#include "Bullet.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"
#include "Collider.h"

Bullet::Bullet(
                GameObject &assGO,
                float angle,
                float newSpeed,
                int newDamage,
                float maxDistance,
                std::string sprite,
                int frameCount,
                float frameTime,
                float secondsToSelfDestruct,
                bool isPlayer,
                bool isEnemy
                ) : Component(assGO),
                    distanceLeft(maxDistance),
                    damage(newDamage),
                    targetsPlayer(isPlayer),
                    targetsEnemy(isEnemy)
{
    Sprite* bulletSprite = new Sprite(associated, sprite, frameCount, frameTime, secondsToSelfDestruct);
    associated.AddComponent(bulletSprite);
    Collider* bulletCollider = new Collider(associated);
    associated.AddComponent(bulletCollider);


    speed = {(float)cos(angle) * newSpeed, (float)sin(angle) * newSpeed};
    associated.box.SetCenter(assGO.box.GetCenter());
    associated.angleDeg = speed.GetRotateDegree();
    associated.box.w = bulletSprite->GetWidth();
}

void Bullet::Update(float dt) {
    Vec2 bulletMov(speed.x * dt, speed.y * dt);
    associated.box.SetCenter(associated.box.GetCenter() + bulletMov);

    distanceLeft -= bulletMov.DistToOrigin();

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::NotifyCollision(GameObject &other) {
    if (other.GetComponent("Alien") != nullptr) {
        if (targetsEnemy)
            associated.RequestDelete();
    }
    if (other.GetComponent("PenguinBody") != nullptr) {
        if (targetsPlayer)
            associated.RequestDelete();
    }
    if (other.GetComponent("Minion") != nullptr) {
        if (targetsEnemy)
            associated.RequestDelete();
    }
    if (other.GetComponent("PenguinCannon") != nullptr) {
        if (targetsPlayer)
            associated.RequestDelete();
    }
}

void Bullet::Render() {
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

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::Start() {}