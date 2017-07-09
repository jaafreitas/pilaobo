#include <SoftRcPulseOut.h>

#include "settings.h"
#include "servo.h"

// Minimum time before we can set a new servo position.
#define SERVO_MIN_REFRESH 20

// A higher number decreases the servo velocity.
#define SERVO_PACE 5

int servoPosition = 45;
bool servoInc = true;
unsigned long servoPreviousMillis = 0;

SoftRcPulseOut leftArm;
SoftRcPulseOut rightArm;

void setupServo() {
  leftArm.attach(PIN_ARM_LEFT);
  rightArm.attach(PIN_ARM_RIGHT);
}

void setServo(int distance) {
  unsigned long currentMillis = millis();
  if (currentMillis - servoPreviousMillis >= SERVO_MIN_REFRESH) {

    if (distance < MAX_WORKING_DISTANCE) {
      // We can't assure that we'll have a constant delay between each function call,
      // so to make the servo move at the same speed, we consider the time between
      // the last function call and the current one to increase the step accordingly.
      int servoStep = (currentMillis - servoPreviousMillis) / SERVO_PACE;
  
      if (servoPosition >= 135) {
        servoInc = false;
      }
      if (servoPosition <= 45) {
        servoInc = true;
      }
      
      if (servoInc) {
        servoPosition += servoStep;
      }
      else {
        servoPosition -= servoStep;
      }
    }
    
    leftArm.write(servoPosition);
    rightArm.write(servoPosition);
    SoftRcPulseOut::refresh(1);

    servoPreviousMillis = currentMillis;
  }
}

