// crossing.h
#ifndef CROSSING_H
#define CROSSING_H
#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "tracktimer.h"
#include "armtimer.h"
#include "display.h"
#include "crossingarm.h"
#include "sensors.h"

class Crossing
{
private:
    CrossingArm crossingArm;
    TrackTimer trackTimer1; // track 1 timing
    TrackTimer trackTimer2; // track 2 timing
    Display *display; // display pointer

public:
    Crossing();
    ~Crossing();
    
    Sensors sensorsTrack1;
    Sensors sensorsTrack2;

    LiquidCrystal_I2C *lcd; // pointer of lcd hangs program

    CROSSINGSTATES trackState1 = ST_OFF; // default state of the crossing train 1
    CROSSINGSTATES trackState2 = ST_OFF; // default state of the crossing train 2

    ARMSTATES armState = ST_ARMOFF; // default state of the crossing arm

    void ArmDown();    
    void ArmUp();
    void WaitForTrain(int);
    void WaitForTrainExit(CROSSINGSTATES, int);
    void CheckInSensors();
    void CheckOutSensors();
    void CheckArmUp();
    void CheckArmDown();
    void Init();
};
#endif