#ifndef CROSSINGARM_H
#define CROSSINGARM_H
#include <Arduino.h>
#include <Servo.h>
#include "armtimer.h"

class CrossingArm 
{
private:
    Servo servo;
    int pos;
    bool bellOn;

public:
    ArmTimer armTimer; // arm timing

    CrossingArm();
    ~CrossingArm();

    void ArmUp();
    void ArmDown();
    void Init();
    int GetArmPosition();
};

#endif