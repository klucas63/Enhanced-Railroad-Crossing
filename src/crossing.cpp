#include <Arduino.h>
#include "config.h"
#include "crossing.h"
#include "timers.h"
#include "display.h"

Crossing::Crossing()
{
};

Crossing::~Crossing()
{
};

// crossing init called from setup
void Crossing::Init() {

    Serial.println(F("Initializing"));

    crossingArm.Init(); // call crossing arm init

    display = new Display(); // lcd
    display->DisplayMessage(F("Ready"), 0, DISPTRAIN1);
    display->DisplayMessage(F("Ready"), 0, DISPTRAIN2);
};

// train 1 in sensor 1 
void Crossing::TrainInSensor1() {
    display->DisplayMessage(F("  <<<"), 1, DISPTRAIN1);
    timers.StartTrack1TimeIn(); // start speedo
    WaitForTrain1();
};

// train 1 in sensor 2 other direction
void Crossing::TrainInSensor2() {
    display->DisplayMessage(F("  >>>"), 1, DISPTRAIN1);
    timers.StartTrack1TimeIn(); // start speedo
    WaitForTrain1();
};

// train 2 in sensor 1
void Crossing::TrainInSensor3() {
    display->DisplayMessage(F("  <<<"), 1, DISPTRAIN2);
    timers.StartTrack2TimeIn(); // start speedo
    WaitForTrain2();
};

// train 2 in sensor 2 other direction
void Crossing::TrainInSensor4() {
    display->DisplayMessage(F("  >>>"), 1, DISPTRAIN2);
    timers.StartTrack2TimeIn(); // start speedo
    WaitForTrain2();
};

// train 1 is in so wait
void Crossing::WaitForTrain1() {
    display->DisplayMessage(F("Down"), 0, DISPTRAIN1);
    armState = ST_DOWN; // put the arm down train 1
    timers.StartArmTimeIn(); // start arm timer
};

// train 2 is in so wait
void Crossing::WaitForTrain2() {
    display->DisplayMessage(F("Down"), 0, DISPTRAIN2);
    armState = ST_DOWN; // put the arm down train 2
    timers.StartArmTimeIn(); // start arm timer
};

// move arm for arm down in loop
void Crossing::ArmDown() {
    crossingArm.ArmDown(); // servo logic

    if (crossingArm.GetArmPosition() < MAXARM ) {
        timers.StartArmTimeIn();
    }

    if (crossingArm.GetArmPosition() == MAXARM) {
        Serial.println("stop"); // arm is all the way down
        armState = ST_ARMOFF; // turn off the arm
    }
};

// train out sensor 1 from loop
void Crossing::TrainOutSensor1() {
    if(trackState1 == ST_FLASHING1) {
        display->DisplayMessage(F("Out"), 0, DISPTRAIN1);
        display->DisplayMessage(F(""), 1, DISPTRAIN1);
    }
    else if(trackState1 == ST_FLASHING2) {
        display->DisplaySpeed(DISPTRAIN1, timers.GetStartTrack1TimeIn());
    }

    WaitForTrain1Exit();
};

// train out sensor 2 from loop
void Crossing::TrainOutSensor2() {
    if(trackState1 == ST_FLASHING2) {
        display->DisplayMessage(F("Out"), 0, DISPTRAIN1);
        display->DisplayMessage(F(""), 1, DISPTRAIN1);
    }
    else if(trackState1 == ST_FLASHING1) {
        display->DisplaySpeed(DISPTRAIN1, timers.GetStartTrack1TimeIn());
    }

    WaitForTrain1Exit();
};

// train out from sensor 3 from loop
void Crossing::TrainOutSensor3() {
    if(trackState2 == ST_FLASHING1) {
        display->DisplayMessage(F("Out"), 0, DISPTRAIN2);
        display->DisplayMessage(F(""), 1, DISPTRAIN2);
    }
    else if(trackState2 == ST_FLASHING2) {
        display->DisplaySpeed(DISPTRAIN2, timers.GetStartTrack2TimeIn());
    }

    WaitForTrain2Exit();
};

// train out from sensor 4 from loop
void Crossing::TrainOutSensor4() {
    if(trackState2 == ST_FLASHING2) {
        display->DisplayMessage(F("Out"), 0, DISPTRAIN2);
        display->DisplayMessage(F(""), 1, DISPTRAIN2);
    }
    else if(trackState2 == ST_FLASHING1) {
        display->DisplaySpeed(DISPTRAIN2, timers.GetStartTrack2TimeIn());
    }

    WaitForTrain2Exit();
};

// wait for train to exit track 1
// both sensors 1 and 2 in end up here
void Crossing::WaitForTrain1Exit() {
    if (trackState1 == ST_FLASHING1 || trackState1 == ST_FLASHING2) {
        display->DisplayMessage(F("Up"), 0, DISPTRAIN1);
        trackState1 = ST_OFF; // train 1 left
    }

    if (trackState1 == ST_OFF && trackState1 == ST_OFF) {
        armState = ST_UP; // both trains left raise the arm
    }
};

// wait for train to exit track 2
// both sensors 3 and 4 in end up here
void Crossing::WaitForTrain2Exit() {
    if (trackState2 == ST_FLASHING1 || trackState2 == ST_FLASHING2) {
        display->DisplayMessage(F("Up"), 0, DISPTRAIN2);
        trackState2 = ST_OFF; // train 2 left
    }

    if (trackState1 == ST_OFF && trackState1 == ST_OFF) {
        armState = ST_UP; // both trains left raise the arm
    }
};

// move arm for arm up in loop
void Crossing::ArmUp() {
    crossingArm.ArmUp();

    if (crossingArm.GetArmPosition() == MINARM) {
        armState = ST_ARMOFF; // arm is all the way up
        Serial.println("stop");
        display->DisplayMessage(F("Wait"), 0, DISPTRAIN1);
        display->DisplayMessage(F("Wait"), 0, DISPTRAIN2);
    }
};

// check sensors for train in from main loop
// sensors go low if train is present
void Crossing::CheckInSensors() {
    if (trackState1 == ST_OFF) {
        if (sensor1 < ACTIVESENSOR && timers.CheckTrack1Time()) {
            sensor1 = RESETSENSOR; // set sensor value here so Out isnt checked
            trackState1 = ST_FLASHING1;
            TrainInSensor1();
        }
        else if (sensor2 < ACTIVESENSOR && timers.CheckTrack1Time()) {
            sensor2 = RESETSENSOR; // set sensor value here so Out isnt checked
            trackState1 = ST_FLASHING2;
            TrainInSensor2();
        }
    }

    if (trackState2 == ST_OFF) {
        if (sensor3 < ACTIVESENSOR && timers.CheckTrack2Time()) {
            sensor3 = RESETSENSOR; // set sensor value here so Out isnt checked
            trackState2 = ST_FLASHING1;
            TrainInSensor3();
        }
        else if (sensor4 < ACTIVESENSOR && timers.CheckTrack2Time()) {
            sensor4 = RESETSENSOR; // set sensor value here so Out isnt checked
            trackState2 = ST_FLASHING2;
            TrainInSensor4();
        }
    }
};

// check sensors for train out from main loop
// sensors go low if train is present
void Crossing::CheckOutSensors() {
    if (trackState1 != ST_OFF) {
        // we have a train in track 1
        if (sensor1 < ACTIVESENSOR && timers.CheckTrack1Time()) {
            TrainOutSensor1();
        }
        else if (sensor2 < ACTIVESENSOR && timers.CheckTrack1Time()) {
            TrainOutSensor2();
        }
    }

    if (trackState2 != ST_OFF) {
        // we have a train in track 2
        if (sensor3 < ACTIVESENSOR && timers.CheckTrack2Time()) {
            TrainOutSensor3();
        }
        else if (sensor4 < ACTIVESENSOR && timers.CheckTrack2Time()) {
            TrainOutSensor4();
        }
    }
};

// check for arm up in mail loop
void Crossing::CheckArmUp() {
  if (armState == ST_UP && timers.CheckArmTime()) {
    ArmUp();
  }
};

// check for arm down in main loop
void Crossing::CheckArmDown() {
  if (armState == ST_DOWN && timers.CheckArmTime()) {
    ArmDown();
  }
};

// get input from pin save to crossing main loop
void Crossing::SetSensor1(int sensor1Val) {
    sensor1 = sensor1Val;
};

// get input from pin save to crossing main loop
void Crossing::SetSensor2(int sensor1Val) {
    sensor2 = sensor1Val;
};

// get input from pin save to crossing main loop
void Crossing::SetSensor3(int sensor1Val) {
    sensor3 = sensor1Val;
};

// get input from pin save to crossing main loop
void Crossing::SetSensor4(int sensor1Val) {
    sensor4 = sensor1Val;
};