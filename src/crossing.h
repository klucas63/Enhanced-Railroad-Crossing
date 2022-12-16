// crossing.h
#ifndef CROSSING_H
#define CROSSING_H
#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "timers.h"
#include "display.h"
#include "crossingarm.h"

class Crossing
{
private:
    CrossingArm crossingArm;
    Timers timers; // all timing
    Display *display; // display pointer

    int sensor1; // pin inputs
    int sensor2;
    int sensor3;
    int sensor4;

public:
    Crossing();
    ~Crossing();
    
    LiquidCrystal_I2C *lcd; // pointer of lcd hangs program

    CROSSINGSTATES trackState1 = ST_OFF; // default state of the crossing train 1
    CROSSINGSTATES trackState2 = ST_OFF; // default state of the crossing train 2

    ARMSTATES armState = ST_ARMOFF; // default state of the crossing arm

    void ArmDown();    
    void ArmUp();
    void WaitForTrain1();
    void WaitForTrain2();
    void WaitForTrain1Exit();
    void WaitForTrain2Exit();
    void TrainInSensor1();
    void TrainInSensor2();
    void TrainInSensor3();
    void TrainInSensor4();
    void TrainOutSensor1();
    void TrainOutSensor2();
    void TrainOutSensor3();
    void TrainOutSensor4();
    void CheckInSensors();
    void CheckOutSensors();
    void CheckArmUp();
    void CheckArmDown();
    void Init();
    void SetSensor1(int);
    void SetSensor2(int);
    void SetSensor3(int);
    void SetSensor4(int);
};
#endif