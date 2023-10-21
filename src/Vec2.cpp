#include "Vec2.h"
#include "iostream"

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator+(const Vec2 &vetor2) {
    return Vec2(x + vetor2.x, y + vetor2.y);
}

Vec2 Vec2::operator-(const Vec2 &vetor2) {
    return Vec2(x - vetor2.x, y - vetor2.y);
}

Vec2::~Vec2() {}

Vec2 Vec2::GetRotated(float angulo) {
    return Vec2(x * cos(angulo) - y * sin(angulo),y * cos(angulo) - x * sin(angulo));
}

Vec2 Vec2::DistEntreDoisPontos(Vec2 vetor1, Vec2 vetor2) {
    return Vec2(vetor2.x - vetor1.x,vetor2.y - vetor1.y);
}

float Vec2::DistToOrigin() {
    return (float) sqrt(pow(x,2) + pow(y, 2));
}

void Vec2::RotatedDegree(float angulo) {
    x = GetRotated((angulo * M_PI) / 180).x;
    y = GetRotated((angulo * M_PI) / 180).y;
}

void Vec2::Add(Vec2 vec) {
    x += vec.x;
    y += vec.y;
}

void Vec2::Rotate(float angle) {
    x = x * cos(angle) - y * sin(angle);
    y = y * cos(angle) - x * sin (angle);
}

float Vec2::GetRotateDegree() {
    return atan2(y, x) * (180 / M_PI);
}

void Vec2::RotateDegree(float angle) {
    Rotate((angle *  M_PI) / 180);
}

void Vec2::Sub(Vec2 vec) {
    x -= vec.x;
    y -= vec.y;
}

Vec2 Vec2::VecDefPosByDistanceToObjCentered(Vec2 object, float distance, float angleRad, float w, float h) {
    float xNew = object.x + (distance * cos(angleRad)) - w / 2;
    float yNew = object.y + (distance * sin(angleRad)) - h / 2;
    return Vec2(xNew,yNew);
}

void Vec2::DefPosByDistanceToObjCentered(Vec2 object, float distance, float angleRad, float w, float h) {
    x = object.x + (distance * cos(angleRad)) - w / 2;
    y = object.y + (distance * sin(angleRad)) - h / 2;
}

float Vec2::DistToVec(Vec2 vec) {
    return (float) sqrt(pow((x - vec.x) , 2) + pow((y - vec.y), 2));
}

