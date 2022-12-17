#include <Arduino.h>
#include "config.h"
#include "armtimer.h"

ArmTimer::ArmTimer() {

};

ArmTimer::~ArmTimer() {

};

bool ArmTimer::CheckArmTime() {
    bool bRetVal = false;
    unsigned long current_ms = millis();

    if ((current_ms > arm_ms + ARMSPEED)) {
        bRetVal = true;
        StartArmTimeIn();
    }

    return bRetVal;
};

void ArmTimer::StartArmTimeIn() {
    arm_ms = millis();
};