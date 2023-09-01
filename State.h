#ifndef STATE_H_
#define STATE_H_
#include "Music.h"
#include "Sprite.h"
#endif  // STATE_H_

class State {
    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};


