#include "State.h"
#include <math.h>

State::State(): music("audio/stageState.ogg") {
    GameObject auxGO;
    Sprite* bg = new Sprite(auxGO, "img/ocean.jpg");
    auxGO.AddComponent(bg);
    std::unique_ptr<GameObject> unpGO(auxGO);
    objectArray.push_back(unpGO);
}

State::~State() {
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    State::Input();
    for (int i = objectArray.size() - 1; i > 0; i--) {
        objectArray[i]->Update(dt);
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render() {
    for (auto i = objectArray.end(); i >= objectArray.begin(); i--) {
        (*i)->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject auxGO;
    Sprite* peng = new Sprite(auxGO, "img/penguinface.png");
    auxGO.AddComponent(peng);
    auxGO.box.x = mouseX;
    auxGO.box.y = mouseY;
    Sound* sound = new Sound(auxGO, "audio/boom.wav");
    Face* face = new Face(auxGO);
    auxGO.AddComponent(sound);
    auxGO.AddComponent(face);
    objectArray.emplace_back(auxGO);
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {
        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = objectArray.size() - 1; i >= 0; --i) {
                // Obtem o ponteiro e casta pra Face.
                GameObject* go = (GameObject*) objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains((float)mouseX, (float)mouseY)) {
                    Face* face = (Face*)go->GetComponent("Face");
                    if ( nullptr != face ) {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN) {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quitRequested = true;
            } else {
                Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);  // NOLINT
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}
