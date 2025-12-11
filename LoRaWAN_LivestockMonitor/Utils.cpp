/* 

Laurits M. Jensen - s194279 

*/

#include "Utils.h"
#include <Arduino.h>
//#include <rn2xx3.h>
#include "Config.h"



void led_on() {
  digitalWrite(LED_PIN, 1);
  //digitalWrite(ledPin2, 1);
}

void led_off() {
  digitalWrite(LED_PIN, 0);
  //digitalWrite(ledPin2, 0);
}

