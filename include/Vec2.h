#ifndef INCLUDE_VEC2_H_
#define INCLUDE_VEC2_H_
#define  INCLUDE_SDL
#include "SDL_include.h"
#include <cmath>
#include "math.h"

#define RAD_TO_DEGREE 180/M_PI
#define DEGREE_TO_RAD M_PI/180

class Vec2 {
    public:
        float x, y;
        Vec2();
        Vec2(float x, float y);
        ~Vec2();
        Vec2 operator+(Vec2 const& vetor2) const;
        Vec2 operator-(Vec2 const& vetor2) const;
        Vec2 operator*(const float &rhs) const;
        float DistToOrigin();
        static Vec2 DistEntreDoisPontos(Vec2 vetor1, Vec2 vetor2);
        void incX(float incX);
        void incY(float incY);
        void CalcSpeedAccelerated(float acceleration);
        float Magnitude();
        float DotProduct(Vec2 vetor2);
        Vec2 RotateVec(float angle);
        Vec2 NormalizeVec();
        float GetAngleDeg();
        Vec2 GetRotated(float angulo);
        void Rotate(float angle);
        void RotateDegree(float angle);
        float GetRotateDegree();
        Vec2 VecDefPosByDistanceToObjCentered(Vec2 object, float distance, float angleRad, float w, float h);
        void DefPosByDistanceToObjCentered(Vec2 object, float distance, float angleRad, float w, float h);
        float DistToVec(Vec2 vec);

};

#endif  // INCLUDE_VEC2_H_
