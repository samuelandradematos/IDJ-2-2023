#include "State.h"
#include <math.h>
#include <algorithm>
#include "Collider.h"


State::State(): music("Recursos/audio/stageState.ogg") , started(false), quitRequested(false) {

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
    tileMap = new TileMap((*tileGO),"Recursos/map/tileMap.txt",tileSet);
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

State::~State() {
    delete tileMap;
    delete tileSet;
    objectArray.clear();
}

void State::LoadAssets() {}

void State::Update(float dt) {
    // Carrega a instancia de input
    InputManager &im = InputManager::GetInstance();

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

    std::vector<std::shared_ptr<GameObject>> auxArray;

    for (const auto &it: objectArray) {
        if (it->GetComponent("Collider") != nullptr) {
            auxArray.push_back(it);
        }
    }

    for (int i = auxArray.size() - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            Collider *iCollider = (Collider *) (auxArray.at(i)->GetComponent("Collider"));
            Collider *jCollider = (Collider *) (auxArray.at(j)->GetComponent("Collider"));
            if (
                    Collider::IsColliding(
                            iCollider->box,
                            jCollider->box,
                            auxArray.at(i)->angleDeg * DEGREE_TO_RAD,
                            auxArray.at(j)->angleDeg * DEGREE_TO_RAD
                    )
                )
            {
                auxArray.at(i)->NotifyCollision(*auxArray.at(j));
                auxArray.at(j)->NotifyCollision(*auxArray.at(i));
            }
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
    for (int it = 0; it < objectArray.size();it++) {
        if (!objectArray.at(it)->started)
            objectArray.at(it)->Start();
    }
    started = true;
}

//
std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
    std::shared_ptr<GameObject> sharedPtrGO(go);
    objectArray.emplace_back(sharedPtrGO);
    if (started) {
        sharedPtrGO->Start();
    }
    std::weak_ptr<GameObject> weakPtrGO(sharedPtrGO);
    return weakPtrGO;
}

//
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
    for (const auto &it : objectArray) {
        if (it.get() == go)
            return std::weak_ptr<GameObject>(it);
    }
    return {};
}
