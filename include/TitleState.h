#ifndef INCLUDE_TITLESTATE_H_
#define INCLUDE_TITLESTATE_H_
#include "State.h"

class TitleState : public State {
    public:
        TitleState();
        ~TitleState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};

#endif //INCLUDE_TITLESTATE_H_
