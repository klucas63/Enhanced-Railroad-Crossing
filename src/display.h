// display.h
#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Display 
{
private:
    LiquidCrystal_I2C *lcd;

public:
    Display();
    ~Display();

    void DisplayMessage(String, int, int);
    void DisplaySpeed(int, unsigned long);
};
#endif