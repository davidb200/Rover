///////////////////////////////////////////////////////////////////////
// Title      : UltrasonicSensor.ino
// Authors    : David Betanzos and William Dragstrem
// Description: Implements all the constructors and methods declared in
//              UltrasonicSensor.h.
///////////////////////////////////////////////////////////////////////
#include "UltrasonicSensor.h"


/*
 * Defualt Csontrucotr that intialzies the trigger pin and echo pin to 0
 * @parm  : none
 * @return: void
 *
 */
UltrasonicSensor::UltrasonicSensor(){
  _triggerPin    = 0;
  _echoPin       = 0;
} 


/*
 * Property constructor that sets the trigger pin and echo pin 
 * @parm  : trigger pin and echo pin
 * @return: void
 */
UltrasonicSensor::UltrasonicSensor(byte triggerPin, byte echoPin){
  _triggerPin = triggerPin;
  _echoPin    = echoPin;
} 


/*
 * Measures the duration it takes for the ulatrasonic sensor to recieve a signal
 * that there is a wall.
 * @parm  : none
 * @return: unsigned long
 */
unsigned long UltrasonicSensor::measure(){

  unsigned long duration = 0;

  noInterrupts();
    
  // Setup
  pinMode(_echoPin,OUTPUT);
  digitalWrite(_echoPin, LOW);
    
  // Trigger a measurement
  pinMode(_triggerPin, OUTPUT);
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(5); 
  digitalWrite(_triggerPin,HIGH);
  delayMicroseconds(10); 
  digitalWrite(_triggerPin,LOW);
    
  // Wait for measurement to complete signal
  pinMode(_echoPin,INPUT);
  duration = pulseIn(_echoPin,HIGH,MAX_DURATION);
   
  // Turn interrupts back on
  interrupts();
    
  if(duration > 0)
    duration = duration / 2;
    
  return duration;
} // measure


/*
 * Measures the distance (in inches) the ultrasonic sensor reads
 * from a wall.
 * @parm  : none
 * @return: double
 */
double UltrasonicSensor::measureInches(){

    double inches = 0;
    unsigned long duration = measure();
    
    if(duration > 0)
      inches = duration / 74.0;
    else
      inches = MAX_DURATION / 74.0;
  
    return inches;
} // measureInches