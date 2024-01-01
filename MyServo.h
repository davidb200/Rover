///////////////////////////////////////////////////////////////////////////////////////
// Title       : MyServo.h
// Authors     : David Betanzos and William Dragstrem
// Description : Provides the necessary attributes and methods needed for the servo
//               that the rover uses.
// Attributes  : servo pin and an object of servo
// Enum        : Servo Direction for better code readability
// Constructors: Default Construcotr that intialzies all aattributes to 0 or empty and
//               property constructor that initializes the servo pin
// Methods     : initServo, lookStraight, turnLeft, turnRight
///////////////////////////////////////////////////////////////////////////////////////
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