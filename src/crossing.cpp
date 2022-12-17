#include <Arduino.h>
#include "config.h"
#include "crossing.h"
#include "tracktimer.h"
#include "armtimer.h"
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

// train is in so wait
void Crossing::WaitForTrain(int train) {
    display->DisplayMessage(F("Down"), 0, train);
    armState = ST_DOWN; // put the arm down train 1
    armTimer.StartArmTimeIn(); // start arm timer
};

// wait for train to exit track
// both sensors 1 and 2 in end up here
void Crossing::WaitForTrainExit(CROSSINGSTATES trackState, int train) {
    if (trackState == ST_FLASHING1 || trackState == ST_FLASHING2) {
        display->DisplayMessage(F("Up"), 0, train);

        if (train == DISPTRAIN1) {
            trackState1 = ST_OFF; // train 1 left
        }
        if (train == DISPTRAIN2) {
            trackState2 = ST_OFF; // train 2 left
        }
    }

    if (trackState1 == ST_OFF && trackState2 == ST_OFF) {
        armState = ST_UP; // both trains left raise the arm
    }
};

// move arm for arm down in loop
void Crossing::ArmDown() {
    crossingArm.ArmDown(); // servo logic
    if (crossingArm.GetArmPosition() < MAXARM ) {
        armTimer.StartArmTimeIn();
    }

    if (crossingArm.GetArmPosition() == MAXARM) {
        Serial.println("stop"); // arm is all the way down
        armState = ST_ARMOFF; // turn off the arm
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
        if (sensorsTrack1.GetSensor1() < ACTIVESENSOR && trackTimer1.CheckTrackTime()) {
            sensorsTrack1.SetSensor1(RESETSENSOR); // set sensor value here so Out isnt checked
            trackState1 = ST_FLASHING1;
            sensorsTrack1.TrainInSensor1(display, &trackTimer1, DISPTRAIN1);
            WaitForTrain(DISPTRAIN1);
        }
        else if (sensorsTrack1.GetSensor2() < ACTIVESENSOR && trackTimer1.CheckTrackTime()) {
            sensorsTrack1.SetSensor2(RESETSENSOR); // set sensor value here so Out isnt checked
            trackState1 = ST_FLASHING2;
            sensorsTrack1.TrainInSensor2(display, &trackTimer2, DISPTRAIN2);
            WaitForTrain(DISPTRAIN1);
        }
    }

    if (trackState2 == ST_OFF) {
        if (sensorsTrack2.GetSensor1() < ACTIVESENSOR && trackTimer2.CheckTrackTime()) {
            sensorsTrack2.SetSensor1(RESETSENSOR); // set sensor value here so Out isnt checked
            trackState2 = ST_FLASHING1;
            sensorsTrack1.TrainInSensor1(display, &trackTimer2, DISPTRAIN2);
            WaitForTrain(DISPTRAIN2);
        }
        else if (sensorsTrack2.GetSensor2() < ACTIVESENSOR && trackTimer2.CheckTrackTime()) {
            sensorsTrack2.SetSensor2(RESETSENSOR); // set sensor value here so Out isnt checked
            trackState2 = ST_FLASHING2;
            sensorsTrack1.TrainInSensor2(display, &trackTimer2, DISPTRAIN2);
            WaitForTrain(DISPTRAIN2);
        }
    }
};

// check sensors for train out from main loop
// sensors go low if train is present
void Crossing::CheckOutSensors() {
    if (trackState1 != ST_OFF) {
        // we have a train in track 1
        if (sensorsTrack1.GetSensor1() < ACTIVESENSOR && trackTimer1.CheckTrackTime()) {
            sensorsTrack1.TrainOutSensor1(display, &trackTimer2, trackState1, DISPTRAIN1);
            WaitForTrainExit(trackState1, DISPTRAIN1);
        }
        else if (sensorsTrack1.GetSensor2() < ACTIVESENSOR && trackTimer1.CheckTrackTime()) {
            sensorsTrack1.TrainOutSensor2(display, &trackTimer2, trackState1, DISPTRAIN1);
            WaitForTrainExit(trackState1, DISPTRAIN1);
        }
    }

    if (trackState2 != ST_OFF) {
        // we have a train in track 2
        if (sensorsTrack2.GetSensor1() < ACTIVESENSOR && trackTimer2.CheckTrackTime()) {
            sensorsTrack2.TrainOutSensor1(display, &trackTimer2, trackState2, DISPTRAIN2);
            WaitForTrainExit(trackState2, DISPTRAIN2);
        }
        else if (sensorsTrack2.GetSensor2() < ACTIVESENSOR && trackTimer2.CheckTrackTime()) {
            sensorsTrack2.TrainOutSensor2(display, &trackTimer2, trackState2, DISPTRAIN2);
            WaitForTrainExit(trackState2, DISPTRAIN2);
        }
    }
};

// check for arm up in mail loop
void Crossing::CheckArmUp() {
    if (armState == ST_UP && armTimer.CheckArmTime()) {
        ArmUp();
    }
};

// check for arm down in main loop
void Crossing::CheckArmDown() {
    if (armState == ST_DOWN && armTimer.CheckArmTime()) {
        ArmDown();
    }
};