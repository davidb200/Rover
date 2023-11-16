/*
* The main application
*/

#include "UltrasonicSensor.h"
#include "MyServo.h"
#include "Motor.h"
#include "Remote.h"
#include "Robot.h"

// Constants

// Ultrasonic sensor
const unsigned long MAX_DURATION        = 12 * 12 * 74 * 2; // I chose 12ft
const double FORWARD_DISTANCE_THRESHOLD = 10;
const double SIDE_DISTANCE_THRESHOLD    = 10.5;
const double TOO_CLOSE_THRESHOLD        = 3.0;

const byte TRIGGER_PIN                  = A1;
const byte ECHO_PIN                     = A0;

// Servo
const byte SIGNAL_PIN                   = A2;
const int MIN                           = 500;
const int MAX                           = 2500;

// Motor
const byte LE                           = 5;  // Left enable Timer-0 (OC0B)
const byte LB                           = 7;  // Left backwards
const byte LF                           = 4; // Left forwards

const byte RE                           = 6;  // Right enable Timer-0 (OC0A)
const byte RB                           = 8;  // Right backwards
const byte RF                           = 2; // Right forwards

// LED's
const byte RED_LED                      = A4;
const byte GREEN_LED                    = A5;

// Global variables

// Ultrasonic sensor
UltrasonicSensor us_sensor(TRIGGER_PIN,ECHO_PIN);
double straights_current_distance;
double lefts_current_distance;
double rights_current_distance;

// Servo
MyServo head(SIGNAL_PIN);

// Motors
Motor left_motor(LF,LB,LE);
Motor right_motor(RF,RB,RE);

void setup(){
  // LED's 
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,HIGH);

  // Ultrasonic Sensor
  Serial.begin(9600);

  // Servo
  head.initServo(SIGNAL_PIN);

  // Motors
  delay(5000);

  
}

void loop(){
  left_motor.setSpeed(100);
  right_motor.setSpeed(100);
  // Take a measurement in the straight direction
  straights_current_distance = us_sensor.measureInches();
  // left_motor.stop();
  left_motor.goForward();
  right_motor.goForward();

  // Here we check if straight's current distance is less than the tolerable distance
  //If true
  if(straights_current_distance < FORWARD_DISTANCE_THRESHOLD)
  {   
      //Turn red LED on and green LED off
      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);
      // Rover comes to a full STOP
      left_motor.stop();
      right_motor.stop();
      //delay(500);
      // If were too close to the wall
      if(straights_current_distance < TOO_CLOSE_THRESHOLD){
        // BACKUP 
        left_motor.goBackward();
        right_motor.goBackward();
        delay(1000);
        left_motor.stop();
        right_motor.stop();
      }
      
      // We need to turn the eyes left
      head.turnLeft();
      // measure left's current distance 
      lefts_current_distance = us_sensor.measureInches();
      // Then turn the eyes right
      head.turnRight();
      // meausre right's current distance
      rights_current_distance = us_sensor.measureInches();
      // If left's current distance is less than right's current distance
      head.lookStraight();
      if(lefts_current_distance < rights_current_distance)
      {
         // We turn the rover right
        left_motor.goForward();
        right_motor.goBackward();

        delay(750);
        left_motor.stop();
        right_motor.stop();
        delay(500);

        left_motor.goForward();
        right_motor.goForward();
      }
  // else
     else
      {
        //We turn the rover left
        left_motor.goBackward();
        right_motor.goForward();

        delay(750);
        left_motor.stop();
        right_motor.stop();
        delay(500);

        left_motor.goForward();
        right_motor.goForward();
      }
  }
  // else (No obstacle is detected near) 
  else 
  {
    // We keep the eyes straight 
    head.lookStraight();

    // Set the red LED off and set the green LED on
    digitalWrite(RED_LED,LOW);
    digitalWrite(GREEN_LED,HIGH); 

    // Move the rover forward

  }
}
