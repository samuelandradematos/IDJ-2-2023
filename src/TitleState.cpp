#include "TitleState.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "Text.h"
#include "Camera.h"


TitleState::TitleState() : State::State() {
    // Create BG
    GameObject* title = new GameObject();
    Sprite* titleSprite = new Sprite(*title,"Recursos/img/title.jpg");
    title->AddComponent(titleSprite);
    State::AddObject(title);

    // Create screen text
    GameObject* titleTextGO = new GameObject();
    std::cout << "TitleState() before text" << std::endl;
    Text* titleText = new Text(
                                *titleTextGO,
                                "Recursos/font/Call_me_maybe.ttf",
                                50,
                                Text::SOLID,
                                "Press SPACE to start the game.",
                                PURPLE,
                                0.2
                            );
    std::cout << "TitleState() after text" << std::endl;
    titleTextGO->AddComponent(titleText);
    Vec2 windowCenter = Game::GetInstance().GetWindowCenter();
    titleTextGO->box.SetCenter(windowCenter);
    State::AddObject(titleTextGO);

    std::cout << "TitleState()" << std::endl;
}

TitleState::~TitleState() {
    #ifdef DEBUG
        std::cout << "~TitleState()" << std::endl;
    #endif // DEBUG
}

void TitleState::Update(float dt) {
    if (started) {
        if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) {
            quitRequested = true;
        }
        if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
            StageState *stageState = new StageState();
            Game::GetInstance().Push(stageState);
        }
        UpdateArray(dt);
    }
}

void TitleState::Resume() {
    Camera::pos = {0,0};
    Render();
}

void TitleState::Start() {
    LoadAssets();
    StartArray();
    started = true;
}

void TitleState::Pause() {}

void TitleState::Render() {
    RenderArray();
}

void TitleState::LoadAssets() {}
