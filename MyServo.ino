//////////////////////////////////////////////////////////////////////////////
// Title      : MyServo.ino
// Authors    : David Betanzos and William Dragstrem
// Description: Implements the constructors and methods declared in MyServo.h.
//////////////////////////////////////////////////////////////////////////////
#include "MyServo.h"


/*
 * Default Consrtructor that intialzies the servo pin to 0
 * @parm  : none
 * @return: void
 */
MyServo::MyServo(){
  _servoPin = 0;
} 


/*
 * Property Consrtructor that sets the servo pin
 * @parm  : servo pin
 * @return: void
 */
MyServo::MyServo(byte servoPin){
  _servoPin = servoPin;
}


/*
 * Attaches the servo so its ready to go
 * @parm  : servo pin
 * @return: void
 */
void MyServo::initServo(byte servoPin){
  _servo.attach(_servoPin,MIN,MAX);
} // initServo


/*
 * Makes the rover's head look straight 
 * @parm  : none
 * @return: void
 */
void MyServo::lookStraight(){
  _servo.write(Direction::LOOK_STRAIGHT);
  delay(475);
} // lookStraight


/*
 * Makes the rover's head look left 
 * @parm  : none
 * @return: void
 */
void MyServo::turnLeft(){
  _servo.write(Direction::LOOK_LEFT);
  delay(475);
} // turnLeft


/*
 * Makes the rover's head look right 
 * @parm  : none
 * @return: void
 */
void MyServo::turnRight(){
  _servo.write(Direction::LOOK_RIGHT);
   delay(475);
} // turnRight