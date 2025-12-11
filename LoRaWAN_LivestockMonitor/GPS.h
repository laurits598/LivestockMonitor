

#include "Config.h"
//#include <Stream.h>

#ifndef TINY_GPS_H
#define TINY_GPS_H

#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <DHT.h>
#include <DHT_U.h>

extern DHT_Unified dht;
extern Adafruit_ADXL345_Unified accel;

// ---------- Constants ----------
//#define NTC_PIN   A3
//#define DHTPIN    6
//#define DHTTYPE   DHT11

// ---------- Function Prototypes ----------
void setupSensors();
void loopSensors();

#endif
