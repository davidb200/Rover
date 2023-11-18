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
const double FORWARD_DISTANCE_THRESHOLD = 16;
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

const int TURN_DELAY                    = 620;
const int ADJUST_DELAY                  = 250;
const int REVERSE_DELAY                 = 1000;

// Remote
const byte IR_RECEIVE_PIN               = 12;

// LED's
const byte RED_LED                      = A4;
const byte GREEN_LED                    = A5;
const byte RC_LED                       = 11;

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

int left_speed  = 105;
int right_speed = 100;

// Remote
Remote remote(IR_RECEIVE_PIN);

void setup(){
  // LED's 
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RC_LED,OUTPUT);

  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RC_LED,LOW);

  // Ultrasonic Sensor
  Serial.begin(9600);

  // Servo
  head.initServo(SIGNAL_PIN);

  // Motors
  delay(5000);

  // Remote
  IrReceiver.begin(IR_RECEIVE_PIN, true);

}

void loop(){
  checkRemote();
  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed);
  // Take a measurement in the straight direction

  roverStraight();
  scanDrive();//scan forward left and right while moving and check if needs to turn  //check if path needs to adjust slightly
}

//ROVER CONTROLS---------------------------------------------
void roverLeft(){
  left_motor.goBackward();
  right_motor.goForward();
}//end left

void roverRight(){
  left_motor.goForward();
  right_motor.goBackward();
}//end right

void roverStraight(){
  left_motor.goForward();
  right_motor.goForward();
}//end straight

void roverReverse(){
  left_motor.goBackward();
  right_motor.goBackward();
}//end backward

void roverStop(){
  left_motor.stop();
  right_motor.stop();
}//end stop

//I/O--------------------------------------------------------------------------------
void checkRemote(){
  if(IrReceiver.decode()) 
  {
    bool remoteControl = false; // Init remote control to false
    Serial.println(IrReceiver.decodedIRData.command);
    if(IrReceiver.decodedIRData.command == Remote::Buttons::POWER){ // If we hit the power button 

      digitalWrite(RC_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);

      remoteControl = true;
      roverStop(); // Stop the motors
      delay(2000);
      IrReceiver.resume();

      while(remoteControl) // While we do not hit the power button again
      {
        if(IrReceiver.decode())
        {
        switch(IrReceiver.decodedIRData.command)
        {
          case Remote::Buttons::LEFT:
            roverLeft();
            delay(150);
            roverStop();
            delay(150);
            break;
          case Remote::Buttons::RIGHT:
            roverRight();
            delay(150);
            roverStop();
            delay(150);
            break;
          case Remote::Buttons::BACKWARDS:
            roverReverse();
            delay(150);
            roverStop();
            delay(150);
            break;
          case Remote::Buttons::FORWARDS:
            roverStraight();
            delay(150);
            roverStop();
            delay(150);
            break;
          case Remote::Buttons::POWER:
            remoteControl = false;
            roverStop();
            digitalWrite(RC_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);
            delay(200);
            
            break; 
        }
        IrReceiver.resume();
        }
      }
    }
    else // If it does not recieve the power button as a signal
    {
      // Does not do anything
      IrReceiver.resume();
    }
  }

} // checkRemote


void scanDrive(){ //scans foward left forward right, to use while MOVING // slightly adjusts path if it detects wall to side, checks for turns if it detects wall in front

      head.lookStraight();
      straights_current_distance = us_sensor.measureInches();
      checkTurn(); //immediately checks if rover needs to turn before scanning elsewhere//checks front
      checkRemote(); //
      
      head.turnLeft(); //check left -------------------------
      // measure left's current distance 
      lefts_current_distance = us_sensor.measureInches(); 
      if (lefts_current_distance < SIDE_DISTANCE_THRESHOLD) //veer right
  {
    digitalWrite(RED_LED,HIGH);
    digitalWrite(GREEN_LED,LOW);

    right_motor.setSpeed(right_speed - 50);
    right_motor.goForward();
    delay(ADJUST_DELAY);
    right_motor.setSpeed(right_speed);
    right_motor.goForward();

    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(RED_LED,LOW);
  }
    checkRemote(); //
    head.lookStraight(); //check middle ----------------------
    straights_current_distance = us_sensor.measureInches();
    checkTurn(); //immediately checks if rover needs to turn before scanning elsewhere //checks middle in between turns

    checkRemote(); //
    head.turnRight();  //check right -------------------------
    // meausre right's current distance
    rights_current_distance = us_sensor.measureInches();  

    if(rights_current_distance < SIDE_DISTANCE_THRESHOLD) //veer left
    {
      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);

      left_motor.setSpeed(left_speed - 50);
      left_motor.goForward(); // must call the goForward functions again so they run with the new speed
      delay(ADJUST_DELAY);
      left_motor.setSpeed(left_speed);
      left_motor.goForward();

      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(RED_LED,LOW);
    }
     checkRemote(); //

}//end scanDrive


void checkTurn(){ //checks if rover needs to turn then takes the necessary action accordingly
  if(straights_current_distance < FORWARD_DISTANCE_THRESHOLD)
  {   
      //Turn red LED on and green LED off
      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);
      // Rover comes to a full STOP
      roverStop();
     
      if(straights_current_distance < TOO_CLOSE_THRESHOLD)
      { // If were too close to the wall
        // BACKUP 
        roverReverse();
        delay(REVERSE_DELAY);
        roverStop();
      }
      
      lookSides(); //look around to find which way to turn

      if(lefts_current_distance < rights_current_distance)
      {
         // We turn the rover right
        roverRight();

        delay(TURN_DELAY);
        roverStop();
        delay(50);

        roverLeft();
        delay(200); //orients the back wheel so it continues straight


        roverStraight();
      }
  // else
     else
      {
        //We turn the rover left
        roverLeft();

        delay(TURN_DELAY);
        roverStop();
        delay(50);

        roverRight();
        delay(200);//orients the back wheel so it continues straight

        roverStraight();
      }
  }
  // else (No obstacle is detected near) 

    // We keep the eyes straight 

    // Set the red LED off and set the green LED on
    digitalWrite(RED_LED,LOW);
    digitalWrite(GREEN_LED,HIGH); 

    // Move the rover forward

}//end checkTurn

void lookSides(){ //scans left and right, for when car is stopped and needs to turn
        // We need to turn the eyes left
      head.turnLeft();
      // measure left's current distance 
      lefts_current_distance = us_sensor.measureInches(); 

      head.turnRight();
      // meausre right's current distance
      rights_current_distance = us_sensor.measureInches();  

      head.lookStraight();
}
