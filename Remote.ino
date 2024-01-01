////////////////////////////////////////////////////////////////////////////
// Title      : Remote.ino
// Authors    : David Betanzos and William Dragstrem
// Description: Implements the constructor and methods declared in Remote.h.
////////////////////////////////////////////////////////////////////////////
#include "Remote.h"


/*
 * Default constructor that initializes remote recieve pin to 0
 * @parm  : none
 * @return: void
 */
Remote::Remote(){

  _recievePin = 0;

}


/*
 * Property= constructor that sets the remote recieve pin
 * @parm  : recieve pin
 * @return: void
 */
Remote::Remote(byte recievePin){
  _recievePin = recievePin;
  Motor left_motor(LF,LB,LE);
  Motor right_motor(RF,RB,RE);
}


/*
 * Controls the left and right motors to go backwards
 * @parm  : none
 * @return: void
 */
void Remote::remoteBackwards(){
  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed);

  left_motor.goForward();
  right_motor.goForward();

  delay(500);

  right_motor.stop();
  delay(500);

} // controlBackwards


/*
 * Controls the left and right motors to turn left
 * @parm  : none
 * @return: void
 */
void Remote::remoteLeft(){
  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed);

  left_motor.goBackward();
  right_motor.goForward();

  delay(500);

  right_motor.stop();
  delay(500);

} // controlBackwards


/*
 * Controls the left and right motors to turn right
 * @parm  : none
 * @return: void
 */
void Remote::remoteRight(){
  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed);

  left_motor.goForward();
  right_motor.goBackward();

  delay(500);

  right_motor.stop();
  delay(500);

} // controlBackwards
