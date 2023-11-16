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