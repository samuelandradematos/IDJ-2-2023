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
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

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
        TileSet* tileSet;
        TileMap* tileMap;
        bool quitRequested;
        void AddObject(int mouseX, int mouseY);
        std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif  // INCLUDE_STATE_H_
