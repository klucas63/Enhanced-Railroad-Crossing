// timers.h
#ifndef TIMERS_H
#define TIMERS_H
#include <Arduino.h>

class Timers {
private:
    unsigned long start1_ms = 0; // speedo track 1
    unsigned long start2_ms = 0; // speedo track 2
    unsigned long arm_ms = 0; // arm timer
    unsigned long lastCheckTrack1_ms = 0; // track 1 timer
    unsigned long lastCheckTrack2_ms = 0; // track 2 timer

public:
    Timers();
    ~Timers();
    
    bool CheckTrack1Time();
    bool CheckTrack2Time();
    bool CheckArmTime();
    void StartTrack1TimeIn();
    void StartTrack2TimeIn();
    void StartArmTimeIn();
    unsigned long GetStartTrack1TimeIn();
    unsigned long GetStartTrack2TimeIn();
};
#endif