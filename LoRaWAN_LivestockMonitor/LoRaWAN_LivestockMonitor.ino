/* 

Laurits M. Jensen - s194279 

This sketch takes starting point in the downlink example sketch from the rn2xx3.h library.
Especially the downlink function in the RN2483.cpp file.

*/

#include "RN2483.h"
#include <rn2xx3.h>
#include <SoftwareSerial.h>
#include "Config.h"
#include "Utils.h"
#include "GPS.h"
#include "PNP_Management.h"
#include "Accelerator.h"
//#include "TTN_Config.h"

SoftwareSerial mySerial(RX_PIN, TX_PIN);  // RX, TX    (Arduino pin: 10, 11)
rn2xx3 myLora(mySerial);                  // Using the rn2xx3 library (Creating a instance)

// the setup routine runs 
// Setup - in case my ex reads this (jk don't even have one)
void setup() {
  //output LED pin
  // Mapping output pins - most arent in use, but still kept for future work.
  pinMode(5, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(57600);   //serial port to computer
  mySerial.begin(9600);  //serial port to radio
  
  /*  Initializing the PNP file - functionality is not implemented....
  Serial.println("Initializing PNP...");
  initPNP();
  */
  delay(2000);

  Serial.println("Setting up LoRaWAN connection...");
  
  // Calls initRadio in RN2483.cpp. Loops untill it has a connection.
  initRadio(mySerial, myLora);
  // Reaching this line means we have a connection. 
  // "ledPin" could be used here with a blue LED "digitalWrite(ledPin, 1);" and function as a connection status.




  //transmit a startup message - a part of one of the example sketches. 
  myLora.tx("TTN Mapper on TTN Enschede node");
  myLora.setDR(2);

  // Initialize the accelerometer 
  Serial.println("Setup done.");
  Serial.println("Init Acce");
  initAcce();
}


String payload;
// Temperature uplink - sent frequently as a part of the testing phase
void txTemp() {
  float temp = getTemp();
  payload = "T:" + String(temp, 2);
  myLora.tx(payload);
}

void checkForFall() {
  unsigned long start = millis();
  unsigned long duration = 10000; // 10 seconds
  bool fallDetected = false;

  while (millis() - start < duration) {
      if (checkAcceEvent_V2()) {
          fallDetected = true;
          break;  // stop early if detected
      }
      delay(10);
  }
  if (fallDetected) {
      myLora.tx("W:FALL_DETECTED");
  }
}

void loop() {
  
  checkForFall();
  Serial.println("Checking accelerator");

  delay(2000); // The delay could cause some issues: If the accelerometer detects a fall inbetween. 
  txTemp();
  
  /* 
  As mentioned in the report, the device has downlink functionality
  To test this, remove the other function calls, so that this loop only contains downlink()
  The Downlink messages can then be sent via the TTN console (HEX format) 
  */
  //led_on();
  //downlink(mySerial, myLora);
  //led_off();

}



















