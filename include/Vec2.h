#ifndef INCLUDE_VEC2_H_
#define INCLUDE_VEC2_H_
#define  INCLUDE_SDL
#include "SDL_include.h"
#include <cmath>
#include "math.h"

class Vec2 {
    public:
        float x, y;
        Vec2();
        Vec2(float x, float y);
        ~Vec2();
        Vec2 operator+(Vec2 const& vetor2);
        Vec2 operator-(Vec2 const& vetor2);
        Vec2 operator*(const float rhs);
        Vec2 somaOuSubtraiVetores(Vec2 vetor1, Vec2 vetor2, int tipo);
        Vec2 multPorEscalar(Vec2 vetor, float escalar);
        float DistToOrigin();
        Vec2 normalizado(Vec2 vetor);
        static Vec2 DistEntreDoisPontos(Vec2 vetor1, Vec2 vetor2);
        float incX(Vec2 vetor);
        float RotateDegree();
        float Magnitude();
        float DotProduct(Vec2 vetor2);
        Vec2 RotateVec(float angle);
        Vec2 NormalizeVec();
        float GetAngleDeg();
        float incEntreDoisPontos(Vec2 vetor1, Vec2 vetor2);
        Vec2 GetRotated(float angulo);
        void RotatedDegree(float angulo);
        void Add(Vec2 vec);
        void Rotate(float angle);
        void RotateDegree(float angle);
        float GetRotateDegree();
        void Sub(Vec2 vec);
        Vec2 VecDefPosByDistanceToObjCentered(Vec2 object, float distance, float angleRad, float w, float h);
        void DefPosByDistanceToObjCentered(Vec2 object, float distance, float angleRad, float w, float h);
        float DistToVec(Vec2 vec);
};

#endif  // INCLUDE_VEC2_H_
