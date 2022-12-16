#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "display.h"
#include "crossing.h"

Display::Display()
{
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->begin();
};

Display::~Display() 
{
};

// this message to be displayed on lcd, thismessage
// line 1 or 2 of lcd, displayline
// train 1 is 0 and train 2 is 9, displaycolumn
void Display::DisplayMessage(String thismessage, int displayLine, int displayColumn)
{
    if (thismessage.length() < DISPLAYLEN) {
        String padded = "        ";
        thismessage += padded.substring(0, DISPLAYLEN - thismessage.length());
    }

    Serial.println(thismessage);
    lcd->setCursor(displayColumn, displayLine);
    lcd->print(thismessage);
};

// train is 1 or 2
// starttime is from the train in sensor
void Display::DisplaySpeed(int train, unsigned long starttime) {
    float in_per_second;
    unsigned long stoptime = millis();
    unsigned long measured_ms;
 
    measured_ms = stoptime - starttime;

    // distance is the distance in mm between your sensors
    if (train == 1) {
        in_per_second = (float)DISTANCE1 * 1000 / measured_ms;
    }
    else {
        in_per_second = (float)DISTANCE2 * 1000 / measured_ms;
    }
    DisplayMessage((String)((int)in_per_second) + F(" MPH"), 1, train);
};