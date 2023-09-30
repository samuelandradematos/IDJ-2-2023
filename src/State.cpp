#include "State.h"
#include <math.h>


State::State(): music("Recursos/audio/stageState.ogg") {
    // Inicialização do criterio de parada
    quitRequested = false;

    // Inicialização do background e da musica
    auto* bgGO = new GameObject();
    Component* bg = (Component*) new Sprite((*bgGO), "Recursos/img/ocean.jpg");
    bgGO->AddComponent(bg);
    Component* cf = (Component*) new CameraFollower((*bgGO));
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


    if (im.KeyPress(SPACE_KEY)) {
        Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI*(rand() % 1001)/500.0) + Vec2((float) im.GetMouseX(), (float) im.GetMouseY());
        AddObject((int)objPos.x + (int) Camera::pos.x, (int)objPos.y + (int) Camera::pos.y);
    }

    for (auto i = objectArray.end() - 1; i >= objectArray.begin(); i--) {
        (*i)->Update(dt);
    }
    for (auto i = objectArray.end() - 1; i >= objectArray.begin(); i--) {
        if ((*i)->IsDead()) {
            objectArray.erase(i);
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

void State::AddObject(int mouseX, int mouseY) {
    auto* auxGO = new GameObject();
    auto* penguin = (Component*) new Sprite((*auxGO), "Recursos/img/penguinface.png");
    auxGO->AddComponent(penguin);
    auxGO->box = {(float)mouseX, (float)mouseY, auxGO->box.w, auxGO->box.h};
    auto* sound = (Component*) new Sound((*auxGO), "Recursos/audio/boom.wav");
    auto* face = (Component*) new Face((*auxGO));
    auxGO->AddComponent(sound);
    auxGO->AddComponent(face);
    objectArray.emplace_back(auxGO);
}

