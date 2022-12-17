#include "config.h"
#include "display.h"
#include "tracktimer.h"
#include "sensors.h"

Sensors::Sensors() {

};

Sensors::~Sensors() {

};

// get input from saved value
int Sensors::GetSensor1() {
    return sensor1;
};

// get input from saved value
int Sensors::GetSensor2() {
    return sensor2;
};

// get input from pin save to crossing main loop
void Sensors::SetSensor1(int sensorVal) {
    sensor1 = sensorVal;
};

// get input from pin save to crossing main loop
void Sensors::SetSensor2(int sensorVal) {
    sensor2 = sensorVal;
};

// train 1 in sensor 1 
void Sensors::TrainInSensor1(Display *display, TrackTimer *timer, int train) {
    display->DisplayMessage(F("  <<<"), 1, train);
    timer->StartTrackTimeIn(); // start speedo
};

// train 1 in sensor 2 other direction
void Sensors::TrainInSensor2(Display *display, TrackTimer *timer, int train) {
    display->DisplayMessage(F("  >>>"), 1, train);
    timer->StartTrackTimeIn(); // start speedo
};

// train out sensor 1 from loop
void Sensors::TrainOutSensor1(Display *display, TrackTimer *timer, CROSSINGSTATES trackState, int train) {
    if(trackState == ST_FLASHING1) {
        display->DisplayMessage(F("Out"), 0, train);
        display->DisplayMessage(F(""), 1, train);
    }
    else if(trackState == ST_FLASHING2) {
        display->DisplaySpeed(train, timer->GetStartTrackTimeIn());
    }
};

// train out sensor 2 from loop
void Sensors::TrainOutSensor2(Display *display, TrackTimer *timer, CROSSINGSTATES trackState, int train) {
    if(trackState == ST_FLASHING2) {
        display->DisplayMessage(F("Out"), 0, train);
        display->DisplayMessage(F(""), 1, train);
    }
    else if(trackState == ST_FLASHING1) {
        display->DisplaySpeed(train, timer->GetStartTrackTimeIn());
    }
};