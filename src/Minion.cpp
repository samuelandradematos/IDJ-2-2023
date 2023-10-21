#include "Minion.h"
#include "random"
#include "chrono"



Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg)
: Component(associated), alienCtr(alienCenter), arc(arcOffsetDeg) {
    Sprite* minionSprite = new Sprite(associated,"Recursos/img/minion.png");
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> gen(1.0,1.5);
    float minionScale = gen(rng);
    std::cout << "minionScale: " << minionScale << std::endl;
    minionSprite->SetScale(minionScale,minionScale);
    associated.AddComponent(minionSprite);

    Vec2 posInit = {0, 0};
    std::cout << "arc: " << arc << std::endl;
    if (auto refCenter = alienCtr.lock()) {
        posInit.DefPosByDistanceToObjCentered(refCenter->box.GetCenter(), DIST_INICIAL, (arc * M_PI / 180), associated.box.w, associated.box.h);

        associated.box.SetPosition(posInit);

        associated.angleDeg = arc;
    }
    else {
        associated.RequestDelete();
    }
}

void Minion::Update(float dt) {

    float minionSpeed = MINION_ANGULARSPEED * dt;
    associated.angleDeg += minionSpeed;

    if (auto center = alienCtr.lock()){
        Vec2 aux = associated.box.GetVector();
        aux.DefPosByDistanceToObjCentered(center->box.GetCenter(), DIST_INICIAL, associated.angleDeg * M_PI / 180,associated.box.w, associated.box.h);
        aux.RotateDegree(minionSpeed);

        associated.box.x = aux.x;
        associated.box.y = aux.y;
    } else {
        associated.RequestDelete();
    }

}

void Minion::Shoot(Vec2 target) {
    Vec2 path = target - associated.box.GetCenter();
    float angle = atan2(path.y, path.x);

    GameObject* bulletGO = new GameObject();
    Bullet* bullet = new Bullet((*bulletGO), angle, MINION_BULLETSPEED, MINION_BULLETDMG, path.DistToOrigin(), "Recursos/img/minionbullet1.png");
    bulletGO->AddComponent(bullet);

    bulletGO->box.SetCenter(associated.box.GetCenter());

    Game::GetInstance().GetState()->AddObject(bulletGO);
}

void Minion::Render() {}

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Start() {}
