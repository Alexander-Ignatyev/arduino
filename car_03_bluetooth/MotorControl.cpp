#include <arduino.h>
#include "MotorControl.h"

MotorControl::MotorControl(int enablePin
      , int controlPin1
      , int controlPin2
      , float correctionFactor)
  : d_enablePin(enablePin)
  , d_controlPin1(controlPin1)
  , d_controlPin2(controlPin2)
  , d_correctionFactor(correctionFactor) {
    pinMode(d_enablePin, OUTPUT);
    pinMode(d_controlPin1, OUTPUT);
    pinMode(d_controlPin2, OUTPUT);
    
    digitalWrite(d_enablePin, LOW);
}

void MotorControl::run(int speed) const {
  speed = constrain(speed*d_correctionFactor, -255, 255);
  const bool forward = speed > 0;
  digitalWrite(d_controlPin1, forward);
  digitalWrite(d_controlPin2, !forward);
  analogWrite(d_enablePin, abs(speed));
}

void MotorControl::stop() const {
  analogWrite(d_enablePin, 0);
}
