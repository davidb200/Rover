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