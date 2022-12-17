#include <Arduino.h>
#include "config.h"
#include "tracktimer.h"

TrackTimer::TrackTimer() 
{
};

TrackTimer::~TrackTimer() 
{
};

bool TrackTimer::CheckTrackTime() {
    bool bRetVal = false;
    unsigned long current_ms = millis();

    if (lastCheckTrack_ms == 0) {
        lastCheckTrack_ms = current_ms;
    }

    if ((current_ms > lastCheckTrack_ms + TIMEOUT)) {
        bRetVal = true;
        lastCheckTrack_ms = current_ms;
    }

    return bRetVal;
};

void TrackTimer::StartTrackTimeIn() {
    start_ms = millis(); // start speedo 
};

unsigned long TrackTimer::GetStartTrackTimeIn() {
    return start_ms;
};