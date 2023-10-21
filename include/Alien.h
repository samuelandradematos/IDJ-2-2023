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

#define ALIEN_SPEED 150
#define ALIEN_HP 30
#define ALIEN_ANGULARSPEED 30

class Alien : public Component {
    public:
        Alien(GameObject& assoGo, int nMns);
        ~Alien();
        void Start();
        void Render();
        void Update(float dt);
        bool Is(std::string type);
        int pNMinions;
    private:
        class Action {
            public:
                enum ActionType {MOVE, SHOOT};
                Action(ActionType type, float x, float y);
                ActionType type;
                Vec2 pos;
        };
        Vec2 speed;
        int hp, nMinions;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;

};

#endif //INCLUDE_ALIEN_H_
