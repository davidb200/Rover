//////////////////////////////////////////////////////////////////////////
// Title       : UltrasonicSensor.h
// Authors     : David Betanzos and William Dragstrem
// Description : Provides the necessary atrributes and methods needed for
//               creating an object of ultrasonic sensor.
// Attributes  : Trigger pin and echo pin
// Constructors: Defualt Constrcutor initalizing all attributes to 0 and 
//               property constructor setting the trigger pin and echo pin
// Methods     : measure and measureInches
///////////////////////////////////////////////////////////////////////////
#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor{
  private:
  byte  _triggerPin;
  byte  _echoPin;

  public:

  ///////////// CONSTRUCTORS /////////////
  UltrasonicSensor();
  UltrasonicSensor(byte triggerPin, byte echoPin);

  ////////////// METHODS ////////////////
  unsigned long measure();
  double measureInches();

}; // UltrasonicSensor

#endif