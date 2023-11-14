#include "Motor.h"

Motor::Motor(){
  _pin1      = 0;
  _pin2      = 0;
  _enable    = 0;
  _speed     = 0;
} 


Motor::Motor(byte pin1, byte pin2, byte enable){
  _pin1      = pin1;
  _pin2      = pin2;
  _enable    = enable;
  _speed     = 0;

  pinMode(_pin1  , OUTPUT);
  pinMode(_pin2  , OUTPUT);
  pinMode(_enable, OUTPUT);
} 


int Motor::getSpeed(){
  return _speed;
} // getSpeed


void Motor::setSpeed(int speed){
  _speed = speed;
} // setSpeed


void Motor::run(Motor::MotorDirection direction){

  switch(direction)
  {
      case MotorStop:
      	digitalWrite(_pin1,LOW);
      	digitalWrite(_pin2,LOW);
      	digitalWrite(_enable,LOW);
      	break;
      case MotorForward:
      	digitalWrite(_pin1,HIGH);
      	digitalWrite(_pin2,LOW);
      	analogWrite(_enable,_speed);
      	break;
      case MotorLeft:
        break;
      case MotorRight:
        break;
  } // which dir

} // run
