#include "MyServo.h"

MyServo::MyServo(){
  _servoPin = 0;
  _position = 0;
} 


MyServo::MyServo(byte servoPin){
  _servoPin = servoPin;
} 
 