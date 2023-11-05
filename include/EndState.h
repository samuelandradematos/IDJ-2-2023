#ifndef INCLUDE_ENDSTATE_H_
#define INCLUDE_ENDSTATE_H_
#include "State.h"
#include "Music.h"

#define WIN_TEXT_COLOR {0, 255, 0, 0}
#define LOSE_TEXT_COLOR {255, 0, 0, 0}

class EndState : public State {
    public:
        EndState();
        ~EndState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
        bool StateInHold();
    private:
        Music* bgMusic;
};


#endif //INCLUDE_ENDSTATE_H_
