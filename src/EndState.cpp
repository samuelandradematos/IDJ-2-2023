#include "EndState.h"
#include "GameData.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "Text.h"
#include "Game.h"
#include "InputManager.h"
#include "TitleState.h"
#include "Camera.h"

EndState::EndState() {

    // Resets camera position
    Camera::pos = {0,0};

    std::cout << "EndState constructor init" << std::endl;
    if (GameData::playerVictory) {
        // Creates BG and Music
        GameObject* winBgGO = new GameObject();
        Sprite* bg = new Sprite(*winBgGO, "Recursos/img/win.jpg");
        winBgGO->AddComponent(bg);
        bgMusic = new Music("Recursos/audio/endStateWin.ogg");
        bgMusic->Play();
        Game::GetInstance().GetCurrentState().AddObject(winBgGO);

        // Creates info text
        GameObject*  infoTextGO = new GameObject();
        Text* infoText = new Text(
                *infoTextGO,
                "Recursos/font/Call_me_maybe.ttf",
                40,
                Text::SOLID,
                "Press ESCAPE to leave the game or SPACE to start again.",
                PURPLE
        );
        infoTextGO->AddComponent(infoText);
        Vec2 windowCenter = Game::GetInstance().GetWindowCenter() - Vec2(0,100);
        infoTextGO->box.SetCenter(windowCenter);
        Game::GetInstance().GetCurrentState().AddObject(infoTextGO);
    } else {
        // Creates BG and Music
        GameObject* loseBgGO = new GameObject();
        Sprite* bg = new Sprite(*loseBgGO, "Recursos/img/lose.jpg");
        loseBgGO->AddComponent(bg);
        bgMusic = new Music("Recursos/audio/endStateLose.ogg");
        bgMusic->Play();
        Game::GetInstance().GetCurrentState().AddObject(loseBgGO);

        // Creates info text
        GameObject*  infoTextGO = new GameObject();
        Text* infoText = new Text(
                                    *infoTextGO,
                                    "Recursos/font/Call_me_maybe.ttf",
                                    40,
                                    Text::SOLID,
                                    "Press ESCAPE to leave the game or SPACE to start again.",
                                    PURPLE
                                );
        infoTextGO->AddComponent(infoText);
        Vec2 windowCenter = Game::GetInstance().GetWindowCenter() - Vec2(0,100);
        infoTextGO->box.SetCenter(windowCenter);
        Game::GetInstance().GetCurrentState().AddObject(infoTextGO);
    }
}

EndState::~EndState() {
    #ifdef DEBUG
        std::cout << "~EndState()" << std::endl;
    #endif // DEBUG
}

void EndState::Update(float dt) {
    if (InputManager::GetInstance().KeyPress(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested()) {
        quitRequested = true;
    }

    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        TitleState* newState = new TitleState();
        Game::GetInstance().Push(newState);
        popRequested = true;
    }

    UpdateArray(dt);
}

void EndState::Render() {
    RenderArray();
}

void EndState::Pause() {}

void EndState::Resume() {}

void EndState::Start() {
    StartArray();
}

void EndState::LoadAssets() {}

bool EndState::StateInHold() {}
