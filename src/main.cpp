#include <Arduino.h>
#include "config.h"
#include "crossing.h"

Crossing crossing;

void setup() {
  pinMode(FLASHER, OUTPUT);
  pinMode(SERVO1PIN, OUTPUT);  
  pinMode(SENSOR1, INPUT);  
  pinMode(SENSOR2, INPUT);  
  pinMode(SENSOR3, INPUT);  
  pinMode(SENSOR4, INPUT);  

  digitalWrite(FLASHER, LOW);

  Serial.begin(115200);

  Serial.println(F("Boot"));
  crossing.Init();
}

// short and fast so we dont miss an event
void loop() {
  crossing.sensorsTrack1.SetSensor1(analogRead(SENSOR1));
  crossing.sensorsTrack1.SetSensor2(analogRead(SENSOR2));
  crossing.sensorsTrack2.SetSensor1(analogRead(SENSOR3));
  crossing.sensorsTrack2.SetSensor2(analogRead(SENSOR4));

  // sensor states
  crossing.CheckInSensors();

  crossing.CheckOutSensors();

  // arm states
  crossing.CheckArmUp();

  crossing.CheckArmDown();
}