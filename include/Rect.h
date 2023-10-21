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
        Vec2 GetCenter();
        void SetCenter(Vec2 box);
        void SetCenter(float x, float y);
        float DistEntreCentrosRect(Rect rect1, Rect rect2);
        bool PontoPertenceRect(Rect rect, Vec2 ponto);
        bool Contains(float pX, float pY);
        Vec2 GetVector();
        void SetPosition(Vec2 pos);
        void SetPosition(float xNew, float yNew);
};

#endif  // INCLUDE_RECT_H_
