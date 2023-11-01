#include "Minion.h"
#include "random"
#include "chrono"
#include "Collider.h"



Minion::Minion(GameObject &assGO, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg)
: Component(assGO), alienCtr(alienCenter), arc(arcOffsetDeg) {
    std::cout << "Minion constructor init" << std::endl;
    Sprite* minionSprite = new Sprite(associated, "Recursos/img/minion.png");
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> gen(1.0,1.5);
    float minionScale = gen(rng);
    minionSprite->SetScale(minionScale,minionScale);
    associated.AddComponent(minionSprite);
    Collider* minionCollider = new Collider(associated);
    associated.AddComponent(minionCollider);



    Vec2 posInit = {0, 0};
    if (auto refCenter = alienCtr.lock()) {
        posInit.DefPosByDistanceToObjCentered(refCenter->box.GetCenter(), DIST_INICIAL, arc * DEGREE_TO_RAD, assGO.box.w, assGO.box.h);

        associated.box.SetPosition(posInit);

        associated.angleDeg = arc;
    }
    else {
        associated.RequestDelete();
    }
    std::cout << "Minion constructor end" << std::endl;
}

void Minion::Update(float dt) {

    float minionSpeed = MINION_ANGULARSPEED * dt;
    associated.angleDeg += minionSpeed;

    if (auto center = alienCtr.lock()){
        Vec2 aux = associated.box.GetVector();
        aux.DefPosByDistanceToObjCentered(
                                    center->box.GetCenter(),
                                    DIST_INICIAL,
                                    associated.angleDeg * DEGREE_TO_RAD,
                                    associated.box.w,
                                    associated.box.h
                                    );

        associated.box.x = aux.x;
        associated.box.y = aux.y;
    } else {
        associated.RequestDelete();
    }

}

void Minion::Shoot(Vec2 target) {
    Vec2 path = target - associated.box.GetCenter();
    float angle = atan2(path.y, path.x);
    int damage = std::rand() % 10 + 10;

    GameObject* bulletGO = new GameObject();
    Bullet* bullet = new Bullet(
                            (*bulletGO),
                            angle,
                            CANNON_BULLET_SPEED,
                            damage,
                            path.DistToOrigin(),
                            "Recursos/img/minionbullet2.png",
                            3,
                            0.15,
                            0,
                            true,
                            false
                            );
    bulletGO->AddComponent(bullet);

    bulletGO->box.SetCenter(associated.box.GetCenter());

    Game::GetInstance().GetState()->AddObject(bulletGO);
}

void Minion::NotifyCollision(GameObject &other) {
    if (other.GetComponent("Bullet") != nullptr) {
        if (((Bullet *) (other.GetComponent("Bullet")))->targetsEnemy) {
            std::cout << "Acertou minion" << std::endl;
            Alien* alienPtr = (Alien*)(alienCtr.lock()->GetComponent("Alien"));
            int damage = ((Bullet *) (other.GetComponent("Bullet")))->GetDamage();
            alienPtr->TakeDamage(damage);
        }
    }
}

void Minion::Render() {
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

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Start() {}
