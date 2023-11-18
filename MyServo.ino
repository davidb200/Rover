#include "MyServo.h"

MyServo::MyServo(){
  _servoPin = 0;
} 


MyServo::MyServo(byte servoPin){
  _servoPin = servoPin;
}


void MyServo::initServo(byte servoPin){
  _servo.attach(_servoPin,MIN,MAX);
} // initServo


void MyServo::lookStraight(){
  _servo.write(Direction::LOOK_STRAIGHT);
  delay(475);
} // lookStraight


void MyServo::turnLeft(){
  _servo.write(Direction::LOOK_LEFT);
  delay(475);
} // turnLeft


void MyServo::turnRight(){
  _servo.write(Direction::LOOK_RIGHT);
   delay(475);
} // turnRight