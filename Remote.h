//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Title       : Remote.h
// Authors     : David Betanzos and William Dragstrem
// Description : Provides all the necessary attributes and methods needed for and object
//               of Remote.
// Attributes  : Motor attributes needed here to control speed of left and right
//               motors (left enable, left backwards, left forwards, left speed, right enable, right backwards, 
//               right forwards, right speed) and recieve pin
// Constructors: Default constructor initalizing recieve pin to 0 and property constructor
//               that sets the recieve pin
// Methods     : remoteBackwards, remoteLeft, remoteRight
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef REMOTE_H
#define REMOTE_H

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
    BACKWARDS = 82, // Button 8
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