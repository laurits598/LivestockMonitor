/* 

Laurits M. Jensen - s194279 

*/

#pragma once  // prevents multiple inclusion

// RN2483 pins (My own RN2483 module)
#define RX_PIN 10
#define TX_PIN 11
#define RESET_PIN 7
#define LED_PIN 13

// GPS pins
#define GPS_RX 9
#define GPS_TX 8

/* The RN2483 module from the course has a different pin-layout than my own. TX and RX are flipped */
// RN2483 pins (Course RN2483 module)
// #define RX_PIN 11
// #define TX_PIN 10
// #define RESET_PIN 7
// #define LED_PIN 13

// PNP pins
// #define INTERRUPT_PIN 2

// Temp sensor
#define DHTPIN 6
#define DHTTYPE DHT11
#define NTC_PIN A3
// Baud
#define BAUD_ARDU 57600
#define BAUD_LORA 9600

const int ledPin = 5; // Not used, but is embedded in the code. Could have been used for a blue LED after successfull TTN connect
                      // Also should not be defined in *.h file, but compiler hasn't complained