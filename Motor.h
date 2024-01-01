///////////////////////////////////////////////////////////////////////////////////////////////////////
// Title       : Motor.h
// Authors     : David Betanzos and William Dragstrem
// Description : Provides the necessary attributes anbd methods needed for and object
//               of Motor.
// Attributes  : pin 1, pin 2, enable pin, and speed pin
// Constructors: Defualt constructor intiaizling all attrbiutes to 0 and
//               property constructor setting up pin 1, pin 2, enable pin, and speed pin for the wheels.
// Methods     : getSpeed, setSpeed, goForward, goBackward, stop
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MOTOR_H
#define MOTOR_H

class Motor{
  private:
  byte _pin1;
  byte _pin2;
  byte _enable;
  byte _speed;

  public:
   // Enum
  enum MotorDirection{
    MotorStop   ,
    MotorForward,
    MotorLeft   ,
    MotorRight
  }; // MotorDir

  ////////////// CONSTRUCTORS //////////////
  Motor();
  Motor(byte _pin1, byte _pin2, byte _enable);

  ///////////// METHODS ///////////////////
  // Getter
  int getSpeed();
  // Setter
  void setSpeed(int _speed);

  void goForward();
  void goBackward();
  void stop();

}; // Motor
#endif