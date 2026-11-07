#pragma once
class Motor{
    private:

    public:
    Motor(const int IN1p,const int IN2Np, int offs);
    void move(int in1, bool in2);
    void move_int(int speed);
    void stop();
    const int IN1pin;
    const int IN2pin;
    const int offset;

};