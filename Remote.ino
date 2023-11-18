#include "Remote.h"

Remote::Remote(){

  _recievePin = 0;

}


Remote::Remote(byte recievePin){
  _recievePin = recievePin;
  Motor left_motor(LF,LB,LE);
  Motor right_motor(RF,RB,RE);
}


void Remote::remoteBackwards(){
  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed);

  left_motor.goForward();
  right_motor.goForward();

  delay(500);

  right_motor.stop();
  delay(500);

} // controlBackwards



void Remote::remoteLeft(){
  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed);

  left_motor.goBackward();
  right_motor.goForward();

  delay(500);

  right_motor.stop();
  delay(500);

} // controlBackwards


void Remote::remoteRight(){
  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed);

  left_motor.goForward();
  right_motor.goBackward();

  delay(500);

  right_motor.stop();
  delay(500);

} // controlBackwards
