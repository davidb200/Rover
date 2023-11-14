#ifndef MOTOR_H
#define MOTOR_H

// Constants
const byte LE                = 4;  // Left enable Timer-0 (OC0B)
const byte LB                = 3;  // Left backwards
const byte LF                = 10; // Left forwards

const byte RE                = 5;  // Right enable Timer-0 (OC0A)
const byte RB                = 6;  // Right backwards
const byte RF                = 11; // Right forwards

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

  void run(Motor::MotorDirection direction);

}; // Motor
#endif