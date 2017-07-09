#include "settings.h"
#include "sensor.h"

// Minimum time before the next reading.
#define SENSOR_MIN_REFRESH 200

// The "Pace of Sound" at 20 Celsius degrees is 29.1
#define PACE_OF_SOUND 29.1

// HC-SR04 min range in centimeter.
#define SENSOR_MIN_RANGE 2

#define SENSOR_MIN_DURATION SENSOR_MIN_RANGE * PACE_OF_SOUND * 2
#define SENSOR_MAX_DURATION MAX_WORKING_DISTANCE * PACE_OF_SOUND * 2

float sensorDistance = MAX_WORKING_DISTANCE;
unsigned long sensorPreviousMillis = 0;

void setupSensor() {
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

int readSensor() {
  unsigned long currentMillis = millis();
  if (currentMillis - sensorPreviousMillis >= SENSOR_MIN_REFRESH) {
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    long duration = pulseIn(PIN_ECHO, HIGH, SENSOR_MAX_DURATION);
    // When we have a timeout, the duration is close to zero.
    if (duration < SENSOR_MIN_DURATION) {
      duration = SENSOR_MAX_DURATION;
    }
    sensorDistance = (duration / 2) / PACE_OF_SOUND;

    sensorPreviousMillis = currentMillis;
  }

  return sensorDistance;
}

