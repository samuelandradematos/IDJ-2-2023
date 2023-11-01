#ifndef INCLUDE_ALIEN_H_
#define INCLUDE_ALIEN_H_
#include "Component.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include <vector>
#include <queue>
#include <memory>
#include <cmath>
#include "Game.h"
#include "Minion.h"
#include <algorithm>
#include "Timer.h"
#include "PenguinBody.h"

#define ALIEN_SPEED 75
#define ALIEN_HP 30
#define ALIEN_ANGULARSPEED 15
#define ALIEN_REST_TIME 3
#define ALIEN_DEATH_FRAME_COUNT 4
#define ALIEN_DEATH_FRAME_TIME 6
#define MIN_SHOOT_DISTANCE 10
#define DIST_MINIONS 160

class Alien : public Component {
    public:
        Alien(GameObject& assoGo, int nMns);
        ~Alien();
        void Start();
        void Render();
        void Update(float dt);
        bool Is(std::string type);
        static int alienCount;
        void NotifyCollision(GameObject& other);
        void TakeDamage(int damage);
        bool IsDead();
    private:
//        class Action {
//            public:
//                enum ActionType {MOVE, SHOOT};
//                Action(ActionType type, float x, float y);
//                ActionType type;
//                Vec2 pos;
//        };
        enum AlienState {MOVING, RESTING};
        AlienState state;
        Vec2 speed;
        int hp, nMinions;
        Timer restTimer;
        Vec2 destination;
        bool xMovFisinhed, yMovFinished;
        std::vector<std::weak_ptr<GameObject>> minionArray;

};

#endif //INCLUDE_ALIEN_H_
