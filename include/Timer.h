#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

class Timer {
    public:
        Timer();
        void Update(float dt);
        void Restart();
        float Get();
    private:
        float time;
};

#endif //INCLUDE_TIMER_H_
