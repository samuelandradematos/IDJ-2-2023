#ifndef INCLUDE_STAGESTATE_H_
#define INCLUDE_STAGESTATE_H_
#include <iostream>
#include <vector>
#include <memory>
#include "State.h"
#include "Music.h"
#include "TileSet.h"


class StageState : public State {
    public:
        StageState();
        ~StageState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
        bool StateInHold();
    private:
        Music music;
        TileSet* tileSet;
};

#endif  // INCLUDE_STAGESTATE_H_
