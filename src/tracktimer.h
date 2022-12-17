// timers.h
#ifndef TRACKTIMER_H
#define TRACKTIMER_H
#include <Arduino.h>

class TrackTimer {
private:
    unsigned long start_ms = 0; // speedo
    unsigned long lastCheckTrack_ms = 0; // track timer

public:
    TrackTimer();
    ~TrackTimer();
    
    bool CheckTrackTime();
    void StartTrackTimeIn();
    unsigned long GetStartTrackTimeIn();
};
#endif