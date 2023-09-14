#include "Rect.h"

Rect::Rect() {
    this->x = 0;
    this->y = 0;
    this->h = 0;
    this->w = 0;
}

Rect::Rect(float x, float y, float h, float w) {
    this->x = x;
    this->y = y;
    this->h = h;
    this->w = w;
}

Rect::~Rect() {}
