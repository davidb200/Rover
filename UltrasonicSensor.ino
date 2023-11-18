#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(){
  _triggerPin    = 0;
  _echoPin       = 0;
} 


UltrasonicSensor::UltrasonicSensor(byte triggerPin, byte echoPin){
  _triggerPin = triggerPin;
  _echoPin    = echoPin;
} 


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


double UltrasonicSensor::measureInches(){

    double inches = 0;
    unsigned long duration = measure();
    
    if(duration > 0)
      inches = duration / 74.0;
    else
      inches = MAX_DURATION / 74.0;
  
    return inches;
} // measureInches