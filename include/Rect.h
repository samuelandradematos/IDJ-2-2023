#ifndef INCLUDE_RECT_H_
#define INCLUDE_RECT_H_

class Vec2;

class Rect {
    public:
        float x, y, w, h;
        Rect();
        Rect(float x, float y, float w, float h);
        ~Rect();
        Rect somaVec2(Rect rect, Vec2 vetor);
        Vec2 centroRect(Rect rect);
        float distEntreCentrosRect(Rect rect1, Rect rect2);
        bool pontoPertenceRect(Rect rect, Vec2 ponto);
};

#endif  // INCLUDE_RECT_H_
