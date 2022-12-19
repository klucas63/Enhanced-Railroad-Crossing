// config.h
#ifndef CONFIG_H
#define CONFIG_H

#define ARMINCR 1 // smooth out arm
#define ARMSPEED 150 // speed of crossing arm
#define DISPLAYLEN 8 // half the 16 width of the lcd
#define DISTANCE1 152 // mm between sensor 1 and 2 train 1
#define DISTANCE2 152 // mm between sensor 3 and 4 train 2
#define FLASHER 8 // pin 8
#define MAXARM 90
#define MINARM 0
#define SENSOR1 A0 // track 1, analog
#define SENSOR2 A1 // track 1, analog
#define SENSOR3 A2 // track 2, analog
#define SENSOR4 A3 // track 2, analog
#define SERVO1PIN 7 // pin 7
#define TIMEOUT 2000 // in 2 sec look for train again
#define DISPTRAIN1 0 // lcd column for train 1
#define DISPTRAIN2 9 // lcd column for train 2
#define BELLVOLUME 3 // midi volume
#define ACTIVESENSOR 500 // threshold value for sensor in loop
#define RESETSENSOR 1000 // used in loop to reset
#define ARMDELAY 3000 // delay after lights flash for arm down

enum CROSSINGSTATES
{
  ST_OFF,
  ST_FLASHING1,
  ST_FLASHING2,
}; 

enum ARMSTATES
{
  ST_UP,
  ST_DOWN,
  ST_ARMOFF,
};

#endif