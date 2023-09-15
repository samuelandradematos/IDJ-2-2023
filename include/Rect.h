#ifndef INCLUDE_RECT_H_
#define INCLUDE_RECT_H_
#include "Vec2.h"

class Vec2;

class Rect {
    public:
        float x, y, w, h;
        Rect();
        Rect(float x, float y, float w, float h);
        ~Rect();
        Rect SomaVec2(Rect rect, Vec2 vetor);
        Vec2 CentroRect(Rect rect);
        float DistEntreCentrosRect(Rect rect1, Rect rect2);
        bool PontoPertenceRect(Rect rect, Vec2 ponto);
        bool Contains(float pX, float pY);
};

#endif  // INCLUDE_RECT_H_
