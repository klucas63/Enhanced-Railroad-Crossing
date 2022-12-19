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

bool ArmTimer::ArmDelay() {
    unsigned long current_ms = millis();
    bool bReturn = false;

    if (lastCheckArm_ms == 0) {
        lastCheckArm_ms = current_ms;
    }

    if ((current_ms > lastCheckArm_ms + ARMDELAY)) {
        bReturn = true;
    }

    return bReturn;
};

void ArmTimer::StartArmTimeIn() {
    arm_ms = millis();
};