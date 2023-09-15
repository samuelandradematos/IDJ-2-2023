#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_
#include <iostream>
#include <vector>
#include <memory>
#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sound.h"
#include "Face.h"

class State {
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
    private:
        Music music;
        bool quitRequested;
        void Input();
        void AddObject(int mouseX, int mouseY);
        std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif  // INCLUDE_STATE_H_