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

bool Collider::IsColliding(Rect &a, Rect &b, float angleOfA, float angleOfB) {
    Vec2 A[] = { Vec2( a.x, a.y + a.h ),
                 Vec2( a.x + a.w, a.y + a.h ),
                 Vec2( a.x + a.w, a.y ),
                 Vec2( a.x, a.y )
    };
    Vec2 B[] = { Vec2( b.x, b.y + b.h ),
                 Vec2( b.x + b.w, b.y + b.h ),
                 Vec2( b.x + b.w, b.y ),
                 Vec2( b.x, b.y )
    };

    for (auto& v : A) {
        v = Vec2::Rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
    }

    for (auto& v : B) {
        v = Vec2::Rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();
    }

    Vec2 axes[] = { Vec2::Norm(A[0] - A[1]), Vec2::Norm(A[1] - A[2]), Vec2::Norm(B[0] - B[1]), Vec2::Norm(B[1] - B[2]) };

    for (auto& axis : axes) {
        float P[4];

        for (int i = 0; i < 4; ++i) P[i] = Vec2::Dot(A[i], axis);

        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);

        for (int i = 0; i < 4; ++i) P[i] = Vec2::Dot(B[i], axis);

        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);

        if (maxA < minB || minA > maxB)
            return false;
    }

    return true;
}

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

