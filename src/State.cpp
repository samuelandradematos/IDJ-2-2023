#include "State.h"
#include <math.h>
#include <algorithm>


State::State(): music("Recursos/audio/stageState.ogg") {
    // Inicialização do critério de parada
    quitRequested = false;

    // Inicialização da flag de started
    started = false;

    // Inicialização do background e da música
    auto* bgGO = new GameObject();
    Sprite* bg = new Sprite((*bgGO), "Recursos/img/ocean.jpg");
    bgGO->AddComponent(bg);
    CameraFollower* cf = new CameraFollower((*bgGO));
    bgGO->AddComponent(cf);
    bgGO->box = {0, 0, bgGO->box.w, bgGO->box.h};
    objectArray.emplace_back(bgGO);
    music.Play();

    // Inicialização do TileSet e TileMap
    auto* tileGO = new GameObject();
    tileSet = new TileSet((*tileGO),64,64,"Recursos/img/tileset.png");
    tileMap = new TileMap((*tileGO),"Recursos/map/tileMap.txt",tileSet);
    tileMap->SetParallax(-0.5);
    tileGO->AddComponent (tileMap);
    tileGO->box = {0, 0, tileGO->box.w, tileGO->box.h};
    objectArray.emplace_back(tileGO);

    // Criação do Alien
    auto* alienGO = new GameObject();
    Alien* alien = new Alien((*alienGO),3);
    alienGO->AddComponent(alien);
    alienGO->box.SetCenter({512,300});
    objectArray.emplace_back(alienGO);
}

State::~State() {
    delete tileMap;
    delete tileSet;
    objectArray.clear();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    // Carrega a instancia de input
    InputManager& im = InputManager::GetInstance();

    // Camera
    Camera::Update(dt);

    // Se ESC foi pressionando ou o evento QUIT ocorreu atualiza a flag de quit
    if (im.QuitRequested() || im.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    for (int i = objectArray.size() - 1; i >= 0; i--) {
        objectArray.at(i)->Update(dt);
        if (objectArray.at(i)->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render() {
    for (const auto & i : objectArray) {
        i->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Start() {
    LoadAssets();
    for (auto it : objectArray) {
        if (!it->started)
            it->Start();
    }
    started = true;
}

//
std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
    std::shared_ptr<GameObject> sharedPtrGO(go);
    objectArray.push_back(sharedPtrGO);
    if (started) {
        sharedPtrGO->Start();
    }
    std::weak_ptr<GameObject> weakPtrGO(sharedPtrGO);
    return weakPtrGO;
}

//
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
    for (auto it : objectArray) {
        if (it.get() == go)
            return std::weak_ptr<GameObject>(it);
    }
    return {};
}
