#ifndef STATE_H_
#define STATE_H_
#include <iostream>
#include "Music.h"
#include "Sprite.h"


class State {
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};

#endif  // STATE_H_
