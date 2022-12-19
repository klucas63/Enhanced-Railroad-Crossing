#ifndef ARMTIMER_H
#define ARMTIMER_H

class ArmTimer {
private:
    unsigned long arm_ms = 0; // arm timer
    unsigned long lastCheckArm_ms;

public:
    ArmTimer();
    ~ArmTimer();

    bool ArmDelay();
    bool CheckArmTime();
    void StartArmTimeIn();
};
#endif