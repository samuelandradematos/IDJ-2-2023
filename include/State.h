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
#include "Alien.h"
#include "PenguinBody.h"

class State {
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    private:
        bool started;
        Music music;
        TileSet* tileSet;
        TileMap* tileMap;
        bool quitRequested;
        void AddObject(int mouseX, int mouseY);
        std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif  // INCLUDE_STATE_H_
