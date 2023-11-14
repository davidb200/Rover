#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

// Constants
const unsigned long MAX_DURATION = 12 * 12 * 74 * 2; // I chose 12ft
const double DISTANCE_THRESHOLD  = 7.0;
const long TM1_COUNT             = 65536 - (2000000.f / (1.f / (16.f / 1024.f))); // 2000000 is 2 sec's

const byte TRIGGER_PIN           = A1;
const byte ECHO_PIN              = A0;

class UltrasonicSensor{
  private:
  byte  _triggerPin;
  byte  _echoPin;

  public:

  ///////////// CONSTRUCTORS /////////////
  UltrasonicSensor();
  UltrasonicSensor(byte triggerPin, byte echoPin);

  ////////////// METHODS ////////////////
  void setupTimer1();
  unsigned long measure();
  double measureInches();

}; // UltrasonicSensor

#endif