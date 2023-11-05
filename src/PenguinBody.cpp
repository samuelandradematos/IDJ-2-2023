#include "PenguinBody.h"
#include "Collider.h"
#include "InputManager.h"
#include "Sound.h"
#include "Camera.h"
#include "GameData.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject &assGO)
: Component(assGO),
    speed({0, 0}),
    linearSpeed(0),
    angle(0),
    hp(PENGUIN_HP)
{
    Sprite* penguinBody = new Sprite(associated, "Recursos/img/penguin.png");
    associated.AddComponent(penguinBody);
    Collider* pbCollider = new Collider(associated);
    associated.AddComponent(pbCollider);

    player = this;
}

PenguinBody::~PenguinBody() {

    player = nullptr;
    Camera::Unfollow();
    #ifdef DEBUG
        std::cout << "~PenguinBody()" << std::endl;
    #endif // DEBUG
}

void PenguinBody::Start() {
    auto pcGO = new GameObject();
    PenguinCannon* pc = new PenguinCannon(*pcGO,Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
    pcGO->AddComponent(pc);
    pcannon = Game::GetInstance().GetCurrentState().AddObject(pcGO);
    std::cout << "Penguin Body Start" << std::endl;
}

void PenguinBody::Update(float dt) {
    InputManager& im = InputManager::GetInstance();

    if (im.IsKeyDown(SDLK_w)) {
        // Verifies if x speed is higher than max speed
        if (speed.x < BODY_MAX_SPEED) {
            speed.x += BODY_ACCELERATION * dt * std::cos(associated.angleDeg * DEGREE_TO_RAD);
        } else {
            speed.x = BODY_MAX_SPEED;
        }

        // Verifies if y speed is higher than max speed
        if (speed.y < BODY_MAX_SPEED) {
            speed.y += BODY_ACCELERATION * dt * std::sin(associated.angleDeg * DEGREE_TO_RAD);
        } else {
            speed.y = BODY_MAX_SPEED;
        }
    }

    if (im.IsKeyDown(SDLK_s)) {
        // Verifies if x speed is lower than min speed
        if (speed.x > BODY_MIN_SPEED) {
            speed.x -= BODY_ACCELERATION * dt * std::cos(associated.angleDeg * DEGREE_TO_RAD);
        } else {
            speed.x = BODY_MIN_SPEED;
        }

        // Verifies if y speed is lower than min speed
        if (speed.y > BODY_MIN_SPEED) {
            speed.y -= BODY_ACCELERATION * dt * std::sin(associated.angleDeg * DEGREE_TO_RAD);
        } else {
            speed.y = BODY_MIN_SPEED;
        }
    }

    if (im.IsKeyDown(SDLK_a)) {
        angle -= BODY_ANGULAR_SPEED * dt;
    }

    if (im.IsKeyDown(SDLK_d)) {
        angle += BODY_ANGULAR_SPEED * dt;
    }

    if (associated.box.x >= 1408 && speed.x >= 0) {
        associated.box.x = 1408;
    } else {
        associated.box.x += speed.x;
    }

    if (associated.box.x <= 0 && speed.x <= 0) {
        associated.box.x = 0;
    } else {
        associated.box.x += speed.x;
    }

    if (associated.box.y >= 1280 && speed.y >= 0) {
        associated.box.y = 1280;
    } else {
        associated.box.y += speed.y;
    }

    if (associated.box.y <= 0 && speed.y <= 0) {
        associated.box.y = 0;
    } else {
        associated.box.y += speed.y;
    }

    associated.box.GetCenter().Rotate(angle);

    associated.angleDeg = angle * RAD_TO_DEGREE;


    if (IsDead()) {
        std::cout << "Penguin morreu" << std::endl;
        pcannon.lock()->RequestDelete();

        float penguinDeathTimeLimit = 0.2 * PENGUIN_DEATH_FRAME_COUNT + dt;

        GameObject* penguinDeathGO = new GameObject();
        penguinDeathGO->box.SetCenter(associated.box.GetCenter());

        Sprite* penguinDeathSprite = new Sprite(
                *penguinDeathGO,
                "Recursos/img/penguindeath.png",
                4,
                0.2,
                penguinDeathTimeLimit
        );
        penguinDeathGO->AddComponent(penguinDeathSprite);

        Sound* penguinDeathSound = new Sound(*penguinDeathGO,"Recursos/audio/boom.wav");
        penguinDeathSound->Play();
        penguinDeathGO->AddComponent(penguinDeathSound);
        penguinDeathGO->HoldEnd();
        Game::GetInstance().GetCurrentState().AddObject(penguinDeathGO);

        GameData::playerVictory = false;

        Camera::Unfollow();
        associated.RequestDelete();
    }

}

void PenguinBody::NotifyCollision(GameObject &other) {
    if (other.GetComponent("Bullet") != nullptr) {
        Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
        if (bullet->targetsPlayer) {
            static int count = 1;
            std::cout << "PenguinBody collision notified: " << count << std::endl;
            count++;
        }
        if (bullet->targetsPlayer) {
             std::cout << "Acertou player";
            int damage = bullet->GetDamage();
            TakeDamage(damage);
        }
    }
}

void PenguinBody::Render() {
#ifdef DEBUG
    Vec2 center( associated.box.GetCenter() );
    SDL_Point points[5];

    Vec2 point = (Vec2(associated.box.x, associated.box.y) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
                 + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(associated.box.x + associated.box.w, associated.box.y) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
            + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
            + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(associated.box.x, associated.box.y + associated.box.h) - center).RotateVec(associated.angleDeg * DEGREE_TO_RAD)
            + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG

}

bool PenguinBody::Is(std::string type) {
    return type == "PenguinBody";
}

Vec2 PenguinBody::GetPlayerCenteredPos() {
    return associated.box.GetCenter();
}

void PenguinBody::TakeDamage(int damage) {
    hp -= damage;
    std::cout << "Player Took " << damage << " damage. HP left " << hp << std::endl;
}

bool PenguinBody::IsDead() {
    return hp <= 0;
}