#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


void initAcce();
void displaySensorDetails();
void checkAcceEvent();
bool checkAcceEvent_V2();
float getTemp();
