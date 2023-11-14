#ifndef MYSERVO_H
#define MYSERVO_H
#include <Servo.h>

// Constants
const byte SIGNAL_PIN        = A2;
const int MIN                = 500;
const int MAX                = 2500;

class MyServo{
  private:

  byte _servoPin;
  unsigned int _position;
  Servo _servo;

  public:
  // Enum
  enum Direction{
    LOOK_LEFT     = 180,
    LOOK_STRAIGHT = 90,
    LOOK_RIGHT    = 0,
  }; // Direction

  ///////////// CONSTRUCTORS ///////////////
  MyServo();
  MyServo(byte servoPin);

}; // myServo
#endif