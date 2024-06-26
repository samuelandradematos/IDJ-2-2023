#include "Alien.h"
#include "Collider.h"
#include "Sound.h"
#include "GameData.h"


int Alien::alienCount = 0;

Alien::Alien(GameObject &assoGo, int nMns)
: Component(assoGo),
  state{AlienState::RESTING},
  hp(ALIEN_HP),
  nMinions(nMns),
  xMovFinished(false),
  yMovFinished(false)
{
    Sprite* alienSprite = new Sprite(associated,"Recursos/img/alien.png");
    associated.AddComponent(alienSprite);
    Collider* alienCollider = new Collider(associated);
    associated.AddComponent(alienCollider);

    alienCount++;
}

//Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type), pos(x,y) {}

Alien::~Alien() {
    minionArray.clear();
    alienCount--;
    #ifdef DEBUG
        std::cout << "~Alien()" << std::endl;
    #endif // DEBUG
}

void Alien::Start() {
    int distMinions = 360 / nMinions, i = 0;

    while(i < nMinions) {
        GameObject* minionGO = new GameObject();

        Minion* minion = new Minion(*minionGO,Game::GetInstance().GetCurrentState().GetObjectPtr(&associated),distMinions * i);
        minionGO->AddComponent(minion);

        minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(minionGO));
        i++;
    }

    std::cout << "Alien Start" << std::endl;
}

void Alien::Update(float dt) {
    associated.angleDeg += dt * ALIEN_ANGULARSPEED;

    if (PenguinBody::player != nullptr) {
        if (state == AlienState::RESTING) {
            restTimer.Update(dt);
            if (restTimer.Get() >= ALIEN_REST_TIME) {
                restTimer.Restart();
                state = AlienState::MOVING;

                Vec2 playerCenter = PenguinBody::player->GetPlayerCenteredPos();
                float distance = Vec2(associated.box.w / 2, associated.box.h / 2).Magnitude() + DIST_MINIONS;
                float movAngle = (associated.box.GetCenter() - playerCenter).GetAngleDeg();

                destination.DefPosByDistanceToObjCentered(playerCenter,distance, movAngle * DEGREE_TO_RAD,associated.box.w, associated.box.h);
            }
        } else {
            if (xMovFinished && yMovFinished) {
                auto closestMinion = std::min_element(minionArray.begin(), minionArray.end(),
                                                      [&](const std::weak_ptr<GameObject> &minionA,
                                                          const std::weak_ptr<GameObject> &minionB) {
                                                          if (minionA.expired() || minionB.expired())
                                                              return false;

                                                          Vec2 centerA = minionA.lock()->box.GetCenter();
                                                          Vec2 centerB = minionB.lock()->box.GetCenter();

                                                          return Vec2::DistEntreDoisPontos(centerA,
                                                                                           destination).DistToOrigin() <
                                                                 Vec2::DistEntreDoisPontos(centerB,
                                                                                           destination).DistToOrigin();
                                                      });

                if (closestMinion != minionArray.end() && !closestMinion->expired()) {
                    auto minion = closestMinion->lock();
                    Minion *minionPtr = (Minion *) minion->GetComponent("Minion");
                    minionPtr->Shoot(PenguinBody::player->GetPlayerCenteredPos());
                    restTimer.Restart();
                    state = AlienState::RESTING;
                    xMovFinished = false;
                    yMovFinished = false;
                } else {
                    std::cout << "Minion nao existe!" << std::endl;
                }
            } else {
                float alienMov = dt * ALIEN_SPEED;
                Vec2 dist = Vec2::DistEntreDoisPontos(associated.box.GetCenter(), destination);

                if (fabsf(dist.x) > alienMov) {
                    associated.box.x += alienMov * cos(atan2(dist.y, dist.x));
                } else {
                    associated.box.x = destination.x - (associated.box.w / 2);
                    xMovFinished = true;
                }

                if (fabsf(dist.y) > alienMov) {
                    associated.box.y += alienMov * sin(atan2(dist.y, dist.x));
                } else {
                    associated.box.y = destination.y - (associated.box.h / 2);
                    yMovFinished = true;
                }
            }
        }
    }

    if (IsDead()) {
        float alienDeathTimeLimit = dt * ALIEN_DEATH_FRAME_TIME * ALIEN_DEATH_FRAME_COUNT;

        GameObject* alienDeathGO = new GameObject();
        alienDeathGO->box.SetCenter(associated.box.GetCenter());

        Sprite* alienDeathSprite = new Sprite(
                                                *alienDeathGO,
                                                "Recursos/img/aliendeath.png",
                                                4,
                                                dt * ALIEN_DEATH_FRAME_TIME,
                                                alienDeathTimeLimit
                                            );
        alienDeathGO->AddComponent(alienDeathSprite);

        Sound* alienDeathSound = new Sound(*alienDeathGO,"Recursos/audio/boom.wav");
        alienDeathSound->Play();
        alienDeathGO->AddComponent(alienDeathSound);
        alienDeathGO->HoldEnd();
        Game::GetInstance().GetCurrentState().AddObject(alienDeathGO);

        if (alienCount <= 0)
            GameData::playerVictory = true;

        associated.RequestDelete();
    }

}

void Alien::NotifyCollision(GameObject &other) {

    if (other.GetComponent("Bullet") != nullptr) {
        Bullet* bullet = (Bullet *) (other.GetComponent("Bullet"));
        if (bullet->targetsEnemy && bullet->GetDistanceLeft() <= BULLET_MIN_DIST) {
            static int count = 1;
            std::cout << "Alien collision notified: " << count << std::endl;
            std::cout << "Acertou alien" << std::endl;
            int damage = bullet->GetDamage();
            TakeDamage(damage);
            count++;
        }

    }

}

void Alien::Render() {
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

bool Alien::Is(std::string type) {
    return type == "Alien";
}

void Alien::TakeDamage(int damage) {
    hp -= damage;
    std::cout << "Alien Took " << damage << " damage. HP left " << hp << std::endl;
}

bool Alien::IsDead() {
    return hp <= 0;
}