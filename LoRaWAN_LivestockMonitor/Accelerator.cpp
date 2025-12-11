/*

Written by Rasmus Ø
└──> Also responsible for dividing the Main Accelerator.ino code into two different sketches GPS & Accelerator

Refactored by Laurits M. Jensen
└──> I.e. converting the monolithic Accelerator/GPS.ino sketch into proper C++ modules (.cpp/.h) to merge with the LoRa sketch.

*/


#include "Accelerator.h"
#include "Config.h"

uint32_t delayMS;
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
sensors_event_t event; 


void displaySensorDetails(void) {
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void initAcce() {

  //delayMS = sensor.min_delay / 1000;

  Serial.println("Accelerometer Test"); Serial.println("");
  pinMode(9, OUTPUT);  // Set pin 9 as an output
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  accel.setRange(ADXL345_RANGE_16_G);

  displaySensorDetails();
  
  Serial.println("");

}

void checkAcceEvent() {

  /* Get a new sensor event */ 
  accel.getEvent(&event);
 
  if(event.acceleration.x>13){
    Serial.println("--------------------------------CRASH----------------------------------");
  }
  if(event.acceleration.y>13){
    Serial.println("--------------------------------CRASH----------------------------------");
  }
  if(event.acceleration.z>13){
    Serial.println("--------------------------------CRASH----------------------------------");
  }
}

// Revised version to decrease prob of delay - i.e. boost runtime by reducing to 1 if-statement
bool checkAcceEvent_V2() {

  // Read accelerometer event
  accel.getEvent(&event);

  // Compute absolute acceleration on each axis
  float x = fabs(event.acceleration.x);
  float y = fabs(event.acceleration.y);
  float z = fabs(event.acceleration.z);

  // Crash threshold (tweak as needed)
  const float FALL_DETECTED_THRESHOLD = 13.0;

  // Check if ANY axis exceeds the limit
  if (x > FALL_DETECTED_THRESHOLD || y > FALL_DETECTED_THRESHOLD || z > FALL_DETECTED_THRESHOLD) {
    Serial.println("--------------- FALL DETECTED ---------------");
    return true;
  }
  else {
    return false;
  }

}

 
float getTemp() {
  int adcValue = analogRead(NTC_PIN);
  float temp = (1.0 / ((1.0/298.15) - (1.0/3435.0) * log(1023.0 / adcValue - 1.0))) - 273.15;
  Serial.print(temp);
  Serial.println("C");
  return temp;
}











