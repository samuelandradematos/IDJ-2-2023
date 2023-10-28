#include "Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float newSpeed, int newDamage, float maxDistance, std::string sprite, int frameCount, float frameTime)
: Component(associated), distanceLeft(maxDistance), damage(newDamage)  {
     Sprite* bulletSprite = new Sprite(associated, sprite, frameCount, frameTime);
     associated.AddComponent(bulletSprite);

     speed = {(float)cos(angle) * newSpeed, (float)sin(angle) * newSpeed};
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

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::Start() {}