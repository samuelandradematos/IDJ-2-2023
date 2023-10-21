
#include "Alien.h"


Alien::Alien(GameObject &assoGo, int nMns) : Component(assoGo), hp(ALIEN_HP), nMinions(nMns)  {
    Sprite* alienSprite = new Sprite(associated,"Recursos/img/alien.png");
    associated.AddComponent(alienSprite);
    pNMinions = nMinions;
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type), pos(x,y) {}

Alien::~Alien() {
    for (int i = minionArray.size() - 1; i >= 0 ; i--) {
        minionArray.erase(minionArray.begin() + i);
    }
}

void Alien::Start() {
    int distMinions = 360 / nMinions, i = 0;

    while(i < nMinions) {
        GameObject* minionGO = new GameObject();

        Minion* minion = new Minion(*minionGO,Game::GetInstance().GetState()->GetObjectPtr(&associated),distMinions * i);
        minionGO->AddComponent(minion);

        minionArray.push_back(Game::GetInstance().GetState()->AddObject(minionGO));
        i++;

    }
}

void Alien::Update(float dt) {
    associated.angleDeg += dt * ALIEN_ANGULARSPEED;

    InputManager& im = InputManager::GetInstance();

    if (im.MousePress(SDL_BUTTON_LEFT)) {
        taskQueue.emplace(Action(Action::ActionType{Action::SHOOT},im.GetMouseX() + Camera::pos.x, im.GetMouseY() + Camera::pos.y));
    }

    if (im.MousePress(SDL_BUTTON_RIGHT)) {
        taskQueue.emplace(Action(Action::ActionType{Action::MOVE},im.GetMouseX() + Camera::pos.x, im.GetMouseY() + Camera::pos.y));
    }

    if(!taskQueue.empty()) {
        Action aux(Action::ActionType{Action::MOVE}, 0, 0);
        switch (taskQueue.front().type) {
            case Action::MOVE: {
                float alienMov = dt * ALIEN_SPEED;
                bool xMovFinished = false;
                bool yMovFinished = false;
                Vec2 centered = Vec2(associated.box.x + (associated.box.w / 2),
                                     associated.box.y + (associated.box.h / 2));
                Vec2 dist = Vec2::DistEntreDoisPontos(centered, taskQueue.front().pos);

                if (fabsf(dist.x) > alienMov) {
                    associated.box.x += alienMov * cos(atan2(dist.y, dist.x));
                } else {
                    associated.box.x = taskQueue.front().pos.x - (associated.box.w / 2);
                    xMovFinished = true;
                }

                if (fabsf(dist.y) > alienMov) {
                    associated.box.y += alienMov * sin(atan2(dist.y, dist.x));
                } else {
                    associated.box.y = taskQueue.front().pos.y - (associated.box.h / 2);
                    yMovFinished = true;
                }

                if (xMovFinished && yMovFinished) {
                    taskQueue.pop();
                }
            }
                break;
            case Action::SHOOT: {
                Vec2 target = taskQueue.front().pos;
                auto closestMinion = std::min_element(minionArray.begin(), minionArray.end(),
                                                      [&](const std::weak_ptr<GameObject> &minionA,
                                                          const std::weak_ptr<GameObject> &minionB) {
                                                          if (minionA.expired() || minionB.expired())
                                                              return false;

                                                          Vec2 centerA = minionA.lock()->box.GetCenter();
                                                          Vec2 centerB = minionB.lock()->box.GetCenter();

                                                          return Vec2::DistEntreDoisPontos(centerA,
                                                                                           target).DistToOrigin() <
                                                                 Vec2::DistEntreDoisPontos(centerB,
                                                                                            target).DistToOrigin();
                                                      });

                if (closestMinion != minionArray.end() && !closestMinion->expired()) {
                    auto minion = closestMinion->lock();
                    Minion* minionPtr = (Minion*) minion->GetComponent("Minion");
                    minionPtr->Shoot(target);
                } else {
                    std::cout << "Minion nao existe!" << std::endl;
                }
            }
                taskQueue.pop();
                break;

        }
    }

    if (hp <= 0) {
        associated.RequestDelete();
    }

}

void Alien::Render() {}

bool Alien::Is(std::string type) {
    return type == "Alien";
}
