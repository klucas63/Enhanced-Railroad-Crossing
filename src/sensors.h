#ifndef SENSORS_H
#define SENSORS_H

class Sensors {
private:
    int sensor1; // pin inputs
    int sensor2;

public:
    Sensors();
    ~Sensors();

    int GetSensor1();
    int GetSensor2();
    void SetSensor1(int);
    void SetSensor2(int);
    void TrainInSensor1(Display*, TrackTimer*, int);
    void TrainInSensor2(Display*, TrackTimer*, int);
    void TrainOutSensor1(Display*, TrackTimer*, CROSSINGSTATES, int);
    void TrainOutSensor2(Display*, TrackTimer*, CROSSINGSTATES, int);
};
#endif