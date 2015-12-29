#include <NewPing.h>
#include "MotorControl.h"

#define DBG

const int echoPin = 12;
const int triggerPin = 11;
const int maxDistance = 400;
const int desiredDistance = 30;
const int detectionDistance = 100;

NewPing sonar(triggerPin, echoPin, maxDistance);

MotorControl leftMotor(3, 2, 4, 0.75);
MotorControl rightMotor(5, 6, 7);

const int motorSpeed = 160;

void setup() {
  #ifdef DBG
  Serial.begin(9600);
  #endif
}

void loop() {
  const int distance = sonar.ping_cm();
  #ifdef DBG
  Serial.print(distance);
  #endif
  if (distance == 0)
  {
    // do nothing
    #ifdef DBG
    Serial.println(" nothing");
    #endif
  }
  else if (distance < detectionDistance)
  {
    const int sign = distance < desiredDistance ? -1 : 1;
    leftMotor.run(sign*motorSpeed);
    rightMotor.run(sign*motorSpeed);
    Serial.println(sign > 0 ? " forward" : " back");
  }
  else
  {
    leftMotor.stop();
    rightMotor.stop();
    #ifdef DBG
    Serial.println(" stop");
    #endif
  }
  delay(50);
}

