#include <Wire.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define INTERRUPT_PIN 2


Adafruit_ADXL345_Unified accel_pnp = Adafruit_ADXL345_Unified(00001);

volatile bool wake = false;

void wakeISR() {
  wake = true;
}

void configureInterruptADXL() {
  accel_pnp.writeRegister(ADXL345_REG_POWER_CTL, 0x08);

  accel_pnp.writeRegister(ADXL345_REG_ACT_INACT_CTL, 0x70);

  accel_pnp.writeRegister(ADXL345_REG_THRESH_ACT, 40);

  accel_pnp.writeRegister(ADXL345_REG_INT_ENABLE, 0x10);

  accel_pnp.writeRegister(ADXL345_REG_INT_MAP, 0x00);
}

void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
  sleep_disable();
}

void clearADXLInterrupt() {
  byte src = accel_pnp.readRegister(ADXL345_REG_INT_SOURCE);
}

void initPNP() {
  Serial.begin(57600);
  pinMode(INTERRUPT_PIN, INPUT);

  if (!accel_pnp.begin()) {
    Serial.println("ADXL345 not detected.");
    while (1);
  }

  accel_pnp.setRange(ADXL345_RANGE_16_G);
  configureInterruptADXL();

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), wakeISR, RISING);

  Serial.println("System going to sleepmode");
  delay(1000);
}

void loopPNP() {
  if (!wake) {
    goToSleep();
  }


  wake = false;
  clearADXLInterrupt();

  Serial.println("animal have been injured");
  delay(2000);

  Serial.println("Back to sleepmode");
}
 