class MotorControl {
public:
  MotorControl(int enablePin
              , int controlPin1
              , int controlPin2
              , float correctionFactor = 1.0); // speed correction factor must be between 0.0 and 1.0
  void run(int speed) const;
  void stop() const;
private:
  const int d_controlPin1;
  const int d_controlPin2;
  const int d_enablePin;
  const float d_correctionFactor;
};

