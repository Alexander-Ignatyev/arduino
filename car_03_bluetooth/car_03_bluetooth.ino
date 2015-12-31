#include <NewPing.h>
#include <SoftwareSerial.h>
#include "MotorControl.h"

//#define DBG

const int echoPin = 12;
const int triggerPin = 11;
const int maxDistance = 400;
const int desiredDistance = 30;
const int detectionDistance = 100;
const int bluetoothRxPin = 10;
const int bluetoothTxPin = 9;

enum {
  KEEP_DISTANCE_MODE = 0,
  REMOTE_CONTROL_MODE = 1
};

enum {
  RC_MODE = 'M',
  RC_STOP = 'P',
  RC_ARROW_UP = 'U',
  RC_ARROW_DOWN= 'D',
  RC_ARROW_LEFT = 'L',
  RC_ARROW_RIGHT = 'R',
};

int currentMode = KEEP_DISTANCE_MODE;

NewPing sonar(triggerPin, echoPin, maxDistance);

SoftwareSerial btSerial(bluetoothRxPin, bluetoothTxPin);

MotorControl leftMotor(3, 2, 4, 0.75);
MotorControl rightMotor(5, 6, 7);

const int motorSpeed = 160;

void setup() {
  #ifdef DBG
  Serial.begin(9600);
  #endif
  btSerial.begin(9600);
}

void keepDistanceMode();
void remoteControlMode();

void loop() {
  if (btSerial.peek() == RC_MODE) {
    btSerial.read();
    currentMode = !currentMode;
  }

  switch (currentMode) {
  case KEEP_DISTANCE_MODE:
    keepDistanceMode();
    break;
  case REMOTE_CONTROL_MODE:
    remoteControlMode();
    break;
  };
}

void keepDistanceMode() {
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

void remoteControlMode()
{
  if (btSerial.available()) {
    const char control = btSerial.read();
    switch (control) {
    case RC_STOP:
      #ifdef DBG
      Serial.println("RC stop");
      #endif
      leftMotor.stop();
      rightMotor.stop();
      break;
    case RC_ARROW_UP:
      #ifdef DBG
      Serial.println("RC arrow up");
      #endif
      leftMotor.run(motorSpeed);
      rightMotor.run(motorSpeed);
      break;
    case RC_ARROW_DOWN:
      #ifdef DBG
      Serial.println("RC arrow down");
      #endif
      leftMotor.run(-motorSpeed);
      rightMotor.run(-motorSpeed);
      break;
    case RC_ARROW_LEFT:
      #ifdef DBG
      Serial.println("RC arrow left");
      #endif
      leftMotor.run(motorSpeed);
      rightMotor.run(0);
      break;
    case RC_ARROW_RIGHT:
      #ifdef DBG
      Serial.println("RC arrow right");
      #endif
      leftMotor.run(0);
      rightMotor.run(motorSpeed);
      break;
    default:
      #ifdef DBG
      Serial.print("Unknown command ");
      Serial.println(control);
      #endif
      break;
    }
  }
}
