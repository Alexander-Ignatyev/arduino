class MotorControl {
public:
  MotorControl(int enablePin, int controlPin1, int controlPin2);
  void run(int speed) const;
  void stop() const;
private:
  const int d_controlPin1;
  const int d_controlPin2;
  const int d_enablePin;
};

MotorControl leftMotor(3, 2, 4);
MotorControl rightMotor(5, 6, 7);

void setup() {
  leftMotor.run(150);
  rightMotor.run(200);
}

void loop() {
  delay(100);
}

MotorControl::MotorControl(int enablePin, int controlPin1, int controlPin2)
  : d_enablePin(enablePin)
  , d_controlPin1(controlPin1)
  , d_controlPin2(controlPin2) {
    pinMode(d_enablePin, OUTPUT);
    pinMode(d_controlPin1, OUTPUT);
    pinMode(d_controlPin2, OUTPUT);
    
    digitalWrite(d_enablePin, LOW);
}

void MotorControl::run(int speed) const {
  speed = constrain(speed, -255, 255);
  const bool forward = speed > 0;
  digitalWrite(d_controlPin1, forward);
  digitalWrite(d_controlPin2, !forward);
  analogWrite(d_enablePin, abs(speed));
}

void MotorControl::stop() const {
  analogWrite(d_enablePin, 0);
}
