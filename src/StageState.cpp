#include "StageState.h"
#include <algorithm>
#include "CameraFollower.h"
#include "TileMap.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "GameData.h"
#include "EndState.h"
#include "TitleState.h"


StageState::StageState(): State::State(), music("Recursos/audio/stageState.ogg"){

    // Inicialização do background e da música
    GameObject* bgGO = new GameObject();
    Sprite* bg = new Sprite((*bgGO), "Recursos/img/ocean.jpg");
    bgGO->AddComponent(bg);
    CameraFollower* cf = new CameraFollower((*bgGO));
    bgGO->AddComponent(cf);
    bgGO->box = {0, 0, bgGO->box.w, bgGO->box.h};
    objectArray.emplace_back(bgGO);
    music.Play();

    // Inicialização do TileSet e TileMap
    GameObject* tileGO = new GameObject();
    tileSet = new TileSet((*tileGO),64,64,"Recursos/img/tileset.png");
    TileMap* tileMap = new TileMap((*tileGO),"Recursos/map/tileMap.txt",tileSet);
    tileMap->SetParallax(-0.5);
    tileGO->AddComponent (tileMap);
    tileGO->box = {0, 0, tileGO->box.w, tileGO->box.h};
    objectArray.emplace_back(tileGO);

    // Criação do Alien
    GameObject* alienGO = new GameObject();
    Alien* alien = new Alien((*alienGO),3);
    alienGO->AddComponent(alien);
    alienGO->box.SetCenter({512,300});
    objectArray.emplace_back(alienGO);

    // Creation of Penguin
    GameObject* penguinBodyGO = new GameObject();
    PenguinBody* penguinBody = new PenguinBody(*penguinBodyGO);
    penguinBodyGO->AddComponent(penguinBody);
    penguinBodyGO->box.SetCenter({730, 600});
    objectArray.emplace_back(penguinBodyGO);
    Camera::Follow(penguinBodyGO);
}

StageState::~StageState() {
    std::cout << "~StageState()" << std::endl;
    delete tileSet;
}

void StageState::LoadAssets() {}

void StageState::Update(float dt) {
    if (InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) {
        std::cout << "StageState Pop requested" << std::endl;
        popRequested = true;
    }
    if (GameData::playerVictory && PenguinBody::player != nullptr && !objectHoldingEnd) {
        EndState* winState = new EndState();
        Game::GetInstance().Push(winState);
        popRequested = true;
    } else if (!GameData::playerVictory && PenguinBody::player == nullptr && !objectHoldingEnd) {
        EndState* loseState = new EndState();
        Game::GetInstance().Push(loseState);
        popRequested = true;
    }
    UpdateArray(dt);
}

void StageState::Render() {
    RenderArray();
}

void StageState::Start() {
    std::cout << "StageState start" << std::endl;
    LoadAssets();
    StartArray();
}

void StageState::Pause() {}

void StageState::Resume() {}

bool StageState::StateInHold() {}