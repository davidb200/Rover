#ifndef MYSERVO_H
#define MYSERVO_H
#include <Servo.h>

class MyServo{
  private:
  byte _servoPin;
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

  ///////////// METHODS ///////////////
  void initServo(byte servoPin);

  void lookStraight();
  void turnLeft();
  void turnRight();

}; // myServo
#endif