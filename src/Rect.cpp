#include "Rect.h"
#include "iostream"

Rect::Rect() : x(0), y(0), w(0), h(0) {}

Rect::Rect(float xNew, float yNew, float hNew, float wNew) : x(xNew), y(yNew), w(wNew), h(hNew) {}

Rect::~Rect() {}

bool Rect::Contains(float pX, float pY) {
    return ((pX >= x && pX <= x + w) && (pY >= y && pY <= y + h));
}

void Rect::SetCenter(Vec2 box) {
    x = box.x - w / 2;
    y = box.y - h / 2;
}

void Rect::SetCenter(float xNew, float yNew) {
    SetCenter(Vec2(xNew, yNew));
}

Vec2 Rect::GetCenter() {
    return Vec2(x + w / 2, y + h / 2);
}

Vec2 Rect::GetVector() {
    return Vec2(x, y);
}

void Rect::SetPosition(Vec2 pos) {
    x = pos.x;
    y = pos.y;
}

void Rect::SetPosition(float xNew, float yNew) {
    SetPosition(Vec2(xNew,yNew));
}