#include <Arduino.h>
#include "config.h"
#include "timers.h"

Timers::Timers() 
{
};

Timers::~Timers() 
{
};

bool Timers::CheckTrack1Time() {
    bool bRetVal = false;
    unsigned long current_ms = millis();

    if (lastCheckTrack1_ms == 0) {
        lastCheckTrack1_ms = current_ms;
    }

    if ((current_ms > lastCheckTrack1_ms + TIMEOUT)) {
        bRetVal = true;
        lastCheckTrack1_ms = current_ms;
    }

    return bRetVal;
};

bool Timers::CheckTrack2Time() {
    bool bRetVal = false;
    unsigned long current_ms = millis();

    if (lastCheckTrack2_ms == 0) {
        lastCheckTrack2_ms = current_ms;
    }

    if ((current_ms > lastCheckTrack2_ms + TIMEOUT)) {
        bRetVal = true;
        lastCheckTrack2_ms = current_ms;
    }

    return bRetVal;
};

bool Timers::CheckArmTime() {
    bool bRetVal = false;
    unsigned long current_ms = millis();

    if ((current_ms > arm_ms + ARMSPEED)) {
        bRetVal = true;
        StartArmTimeIn();
    }

    return bRetVal;
};

void Timers::StartTrack1TimeIn() {
    start1_ms = millis(); // start speedo track 1
};

void Timers::StartTrack2TimeIn() {
    start2_ms = millis(); // start speedo track 2
};

void Timers::StartArmTimeIn() {
    arm_ms = millis();
};

unsigned long Timers::GetStartTrack1TimeIn() {
    return start1_ms;
};

unsigned long Timers::GetStartTrack2TimeIn() {
    return start2_ms;
};