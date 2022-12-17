#ifndef ARMTIMER_H
#define ARMTIMER_H

class ArmTimer {
private:
    unsigned long arm_ms = 0; // arm timer

public:
    ArmTimer();
    ~ArmTimer();

    bool CheckArmTime();
    void StartArmTimeIn();
};
#endif