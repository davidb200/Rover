//////////////////////////////////////////////////////////////////////////////
// Title      : Motor.ino
// Authors    : David Betanzos and William Dragstrem
// Description: Implements the constructors and methods declared in Motor.h.
//////////////////////////////////////////////////////////////////////////////
#include "Motor.h"


/*
 * Default construcotr that initalizes pin 1, pin 2, enable, and speed
 * to 0
 * @parm  : none
 * @return: void
 */
Motor::Motor(){
  _pin1      = 0;
  _pin2      = 0;
  _enable    = 0;
  _speed     = 0;
} 


/*
 * Property construcotr that sets pin 1, pin 2, and enable pin. Still sets spped to 0.
 * Sets these pins to output
 * @parm  : pin 1, pin 2, enable pin
 * @return: void
 */
Motor::Motor(byte pin1, byte pin2, byte enable){
  _pin1      = pin1;
  _pin2      = pin2;
  _enable    = enable;
  _speed     = 0;

  pinMode(_pin1  , OUTPUT);
  pinMode(_pin2  , OUTPUT);
  pinMode(_enable, OUTPUT);
} 


/*
 * Returns the current speed of the motor
 * @parm  : none
 * @return: int
 */
int Motor::getSpeed(){
  return _speed;
} // getSpeed


/*
 * Sets the speed of the motor
 * @parm  : speed
 * @return: void
 */
void Motor::setSpeed(int speed){
  _speed = speed;
} // setSpeed


/*
 * Makes the motor go forward
 * @parm  : none
 * @return: void
 */
void Motor::goForward(){
  digitalWrite(_pin1, HIGH);
  digitalWrite(_pin2, LOW);
  analogWrite(_enable,_speed);
} // goForward


/*
 * Makes the motor go in reverse
 * @parm  : none
 * @return: void
 */
void Motor::goBackward(){
  digitalWrite(_pin1,LOW);
  digitalWrite(_pin2,HIGH);
  analogWrite(_enable,_speed);
} // goBackward


/*
 * Stops the motor
 * @parm  : none
 * @return: void
 */
void Motor::stop(){
  digitalWrite(_pin1,LOW);
  digitalWrite(_pin2,LOW);
  digitalWrite(_enable,LOW);
} // stop
