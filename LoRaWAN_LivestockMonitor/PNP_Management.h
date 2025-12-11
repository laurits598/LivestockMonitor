#include "Config.h"
#include <Wire.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

void initPNP();
void wakeISR();
void configureInterruptADXL();
void goToSleep();
void clearADXLInterrupt();
void loopPNP();


