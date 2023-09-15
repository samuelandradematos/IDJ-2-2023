#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2::operator+(Vec2 const& vetor2) {
    Vec2 res;
    res.x = x + vetor2.x;
    res.y = y + vetor2.y;
    return res;
}

Vec2::~Vec2() {}

Vec2 Vec2::GetRotated(float angulo) {
    Vec2 vetoraux;
    vetoraux.x = x * cos(angulo) - y * sin(angulo);
    vetoraux.y = y * cos(angulo) - x * sin(angulo);
    return vetoraux;
}
