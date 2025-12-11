/*

Written by Rasmus Ø
└──> Also responsible for dividing the Main Accelerator.ino code into two different sketches GPS & Accelerator

Refactored by Laurits M. Jensen
└──> I.e. converting the monolithic Accelerator/GPS.ino sketch into proper C++ modules (.cpp/.h) to merge with the LoRa sketch.

*/


#include "GPS.h"
#include <SoftwareSerial.h>

//AltSoftSerial ss;  // GPS on pins 8 (RX) and 9 (TX)

// ---------- Global Objects ---------- //
TinyGPS gps;
SoftwareSerial ss(GPS_RX, GPS_TX);


// ============================================================================
//                                SETUP
// ============================================================================
//void setupSensors(Stream &ss) {
void setupSensors() {
  //Serial.begin(9600);
  ss.begin(9600);

  Serial.print("Simple TinyGPS library v. ");
  Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart\n");

  
  //#ifndef ESP8266
  //    while (!Serial); 
  //#endif


  //pinMode(9, OUTPUT);

  Serial.println("GPS Setup - ");
 
  Serial.println("");
}

// ============================================================================
//                                LOOP
// ============================================================================
//void loopSensors(Stream &ss) {
void loopSensors() {

  // ---------- GPS Parsing ----------
  bool newData = false;
  while (ss.available()) {
    char c = ss.read();
    if (gps.encode(c))
      newData = true;
  }

  if (newData) {
    Serial.println("GPS - In if (newData)");
    float flat, flon;
    unsigned long age;

    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial.println();

  
    
  }
}
