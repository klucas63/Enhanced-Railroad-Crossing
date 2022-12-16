#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "config.h"
#include "CrossingArm.h"

SoftwareSerial bellSerial(10, 11);
DFRobotDFPlayerMini bellPlayer;

CrossingArm::CrossingArm() {
};

CrossingArm::~CrossingArm() {

};

void CrossingArm::Init() {
    servo.attach(SERVO1PIN);
    servo.write(MINARM); // default arm up
    pos = MINARM;
    bellOn = false; // default bell off

    bellSerial.begin(9600); // sound comm

    if (!bellPlayer.begin(bellSerial)) {  
        Serial.println(F("DFPlayer offline."));
        while(true);
    }
    Serial.println(F("DFPlayer online."));
};

int CrossingArm::GetArmPosition() {
    return pos;
};

// event for arm down in crossing
void CrossingArm::ArmDown() {
    if (!bellOn) {
        bellPlayer.volume(BELLVOLUME);
        bellPlayer.enableLoopAll();
        digitalWrite(FLASHER, HIGH);
        bellOn = true;
    }

    if (pos < MAXARM) {
        pos = pos + ARMINCR;
        servo.write(pos);
    }
};

// event for arm up in crossing
void CrossingArm::ArmUp() {
    if (bellOn && pos == MINARM+1) {
        digitalWrite(FLASHER, LOW);
        bellPlayer.disableLoopAll();
        bellOn = false;
    }
 
    if (pos > MINARM) {
        pos = pos - ARMINCR;    
        servo.write(pos);
    }
};
