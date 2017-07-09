// Specially developed for Digispark (Default - 16.5mhz) board.

#include "sensor.h"
#include "servo.h"

void setup() {
  setupSensor();
  setupServo();
}

void loop() {
  int distance = readSensor();
  setServo(distance);
}

