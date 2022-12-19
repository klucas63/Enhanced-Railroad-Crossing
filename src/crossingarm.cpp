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

    if (pos < MAXARM ) {
        armTimer.StartArmTimeIn();
    }

    if (bellOn == false && armTimer.ArmDelay()) {
        Serial.println("bell on");
        bellPlayer.volume(BELLVOLUME);
        bellPlayer.enableLoopAll();
        bellOn = true;
    }

    digitalWrite(FLASHER, HIGH);

    if (pos < MAXARM) {
        pos = pos + ARMINCR;
        servo.write(pos);
    } 
    
    if (pos == MAXARM) {
        bellPlayer.disableLoopAll();
        bellOn = false;
    }
};

// event for arm up in crossing
void CrossingArm::ArmUp() {
    if (bellOn) {
        bellPlayer.disableLoopAll();
        bellOn = false;
    }
    
    if (pos > MINARM) {
        pos = pos - ARMINCR;    
        servo.write(pos);
    } 
    
    if (pos == MINARM) {
        digitalWrite(FLASHER, LOW);
    }
};