#include "PenguinBody.h"
#include "Collider.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject &assGO)
: Component(assGO),
    speed({0, 0}),
    linearSpeed(0),
    angle(0),
    hp(PENGUI_HP)
{
    Sprite* penguinBody = new Sprite(associated, "Recursos/img/penguin.png");
    associated.AddComponent(penguinBody);
    Collider* pbCollider = new Collider(associated);
    associated.AddComponent(pbCollider);

    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    auto pcGO = new GameObject();
    PenguinCannon* pc = new PenguinCannon(*pcGO,Game::GetInstance().GetState()->GetObjectPtr(&associated));
    pcGO->AddComponent(pc);
    pcannon = Game::GetInstance().GetState()->AddObject(pcGO);
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

    associated.box.x += speed.x;
    associated.box.y += speed.y;

    associated.box.GetCenter().Rotate(angle);

    associated.angleDeg = angle * RAD_TO_DEGREE;


    if (IsDead()) {
        std::cout << "Penguin morreu" << std::endl;
        pcannon.lock()->RequestDelete();

        float penguinDeathTimeLimit = dt * PENGUIN_DEATH_FRAME_TIME * PENGUIN_DEATH_FRAME_COUNT;

        GameObject* penguinDeathGO = new GameObject();
        penguinDeathGO->box.SetCenter(associated.box.GetCenter());

        Sprite* alienDeathSprite = new Sprite(
                *penguinDeathGO,
                "Recursos/img/penguindeath.png",
                4,
                dt * PENGUIN_DEATH_FRAME_TIME,
                penguinDeathTimeLimit
        );
        penguinDeathGO->AddComponent(alienDeathSprite);

        Sound* penguinDeathSound = new Sound(*penguinDeathGO,"Recursos/audio/boom.wav");
        penguinDeathSound->Play();
        penguinDeathGO->AddComponent(penguinDeathSound);

        Game::GetInstance().GetState()->AddObject(penguinDeathGO);

        Camera::Unfollow();
        associated.RequestDelete();
    }

}

void PenguinBody::NotifyCollision(GameObject &other) {
    if (other.GetComponent("Bullet") != nullptr) {
        if (((Bullet *) (other.GetComponent("Bullet")))->targetsPlayer) {
            if (Vec2::DistEntreDoisPontos(associated.box.GetCenter(),other.box.GetCenter()).Magnitude()
                <= (associated.box.w / 2) ) {
                TakeDamage(((Bullet *) (other.GetComponent("Bullet")))->GetDamage());
            }
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
    std::cout << "Took " << damage << " damage. HP left " << hp << std::endl;
}

bool PenguinBody::IsDead() {
    return hp <= 0;
}