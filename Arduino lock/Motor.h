#include <Servo.h>

class Motor {
  Servo servo;
  int motor_pin;

  public:
    Motor(int motor_pin) : motor_pin(motor_pin) { }

  public:
    void Init() {
      // The servo can not attach a pin before running the Setup function within the ino file.
      // Therefore it cant be placed within the constructor.
      servo.attach(motor_pin);
    }

  public:
    void TurnDegrees(int degrees) {
      servo.write(degrees);
    }
};