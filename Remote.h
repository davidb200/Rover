#ifndef REMOTE_H
#define REMOTE_H
//#define IR_USE_AVR_TIMER1  
#include <IRremote.h>
#include "Motor.h"

class Remote{
  private:
  // Motor
  byte LE                           = 5;  // Left enable Timer-0 (OC0B)
  byte LB                           = 7;  // Left backwards
  byte LF                           = 4;  // Left forwards

  byte RE                           = 6;  // Right enable Timer-0 (OC0A)
  byte RB                           = 8;  // Right backwards
  byte RF                           = 2;  // Right forwards

  int left_speed  = 105;
  int right_speed = 100;

  // Remote
  byte _recievePin;
  public:
  // Enums
  enum Buttons{
    LEFT      = 8,  // Button 4
    RIGHT     = 90, // Button 6
    POWER     = 69, // Power button
    BACKWARDS = 82,  // Button 8
    FORWARDS  = 24  // Button 2

  }; 

  //////// CONSTRUCTORS ////////////////
  Remote();
  Remote(byte recievePin);

  //////////// METHODS /////////////////
  void remoteBackwards();
  void remoteLeft();
  void remoteRight();

}; // Remote

#endif