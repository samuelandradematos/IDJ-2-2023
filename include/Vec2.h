#ifndef INCLUDE_VEC2_H_
#define INCLUDE_VEC2_H_

class Vec2 {
    public:
        float x, y;
        Vec2();
        Vec2(float x, float y);
        ~Vec2();
        Vec2 somaOuSubtraiVetores(Vec2 vetor1, Vec2 vetor2, int tipo);
        Vec2 multPorEscalar(Vec2 vetor, float escalar);
        float magnitude(Vec2 vetor);
        Vec2 normalizado(Vec2 vetor);
        Vec2 distEntreDoisPontos(Vec2 vetor1, Vec2 vetor2);
        float incX(Vec2 vetor);
        float incEntreDoisPonts(Vec2 vetor1, Vec2 vetor2);
        Vec2 rotRad(Vec2 vetor, float angulo);
};

#endif  // INCLUDE_VEC2_H_
