#include "Collider.h"
#include "GameObject.h"
#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#define INCLUDE_SDL
#include "SDL_include.h"
#endif // DEBUG

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
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

Collider::Collider(GameObject &assGO, Vec2 scale, Vec2 offset) : Component(assGO) , scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    box = associated.box;

    box.w *= scale.x;
    box.h *= scale.y;

    box.SetCenter((associated.box.GetCenter() + offset).RotateVec(associated.angleDeg * DEGREE_TO_RAD));
}

bool Collider::Is(std::string type) {
    return type == "Collider";
}

void Collider::SetScale(Vec2 scaleNew) {
    scale = scaleNew;
}

void Collider::SetOffset(Vec2 offsetNew) {
    offset = offsetNew;
}

void Collider::NotifyCollision(GameObject &other) {}

