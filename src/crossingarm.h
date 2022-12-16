#ifndef CROSSINGARM_H
#define CROSSINGARM_H
#include <Arduino.h>
#include <Servo.h>

class CrossingArm 
{
    private:
        Servo servo;
        int pos;
        bool bellOn;

    public:
        CrossingArm();
        ~CrossingArm();

        void ArmUp();
        void ArmDown();
        void Init();
        int GetArmPosition();
};

#endif