////////////////////////////////////////////////////////////////////////////////////////////////////////
// Title      : Rover.ino
// Authors    : David Betanzos and William Dragstrem
// Description: The main application where the functions for the rover are implemented below
//              loop() using the methods provided in all the other source
//              files and called inside loop(). setup() is used to initialize the components needed
//              for the rover: ultrasonic sensor, servo, DC motors, and indicator LED's which 
//              are attached to the back of the rover.
// Functions  : roverLeft, roverRight, roverStraight, roverRevese, checkRemote, scanDrive, checkTurn, 
//              lookSides, veerRight, veerLeft, checkEndCourse          
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UltrasonicSensor.h"
#include "MyServo.h"
#include "Motor.h"
#include "Remote.h"


// Constants

// Ultrasonic sensor
const unsigned long MAX_DURATION        = 12 * 12 * 74 * 2; // I chose 12ft
const unsigned long MAX_DISTANCE        = MAX_DURATION / 74.0; // inches
const double FORWARD_DISTANCE_THRESHOLD = 10.0;
const double SIDE_DISTANCE_THRESHOLD    = 12.6;
const double TOO_CLOSE_THRESHOLD        = 4.0;

const byte TRIGGER_PIN                  = A1;
const byte ECHO_PIN                     = A0;

// Servo
const byte SIGNAL_PIN                   = A2;
const int MIN                           = 500;
const int MAX                           = 2500;

// Motor
const byte LE                           = 5;  // Left enable Timer-0 (OC0B)
const byte LB                           = 7;  // Left backwards
const byte LF                           = 4;  // Left forwards

const byte RE                           = 6;  // Right enable Timer-0 (OC0A)
const byte RB                           = 8;  // Right backwards
const byte RF                           = 2;  // Right forwards

const int TURN_DELAY                    = 500;
const int REVERSE_DELAY                 = 300;

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

int left_speed  = 255; // left speed should be about 10 more than right speed to keep it on a straight course
int right_speed = 245;

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

/*
 * Turns the rover left
 * @parm  : none
 * @return: void
 */
void roverLeft(){
  bool turning = true;
  double straight_previous = us_sensor.measureInches();

  head.turnRight();
  rights_current_distance = us_sensor.measureInches();
  double right_previous = rights_current_distance;

  left_motor.goBackward();
  right_motor.goForward();


  while (turning){
    rights_current_distance = us_sensor.measureInches();
    checkRemote();
  if(rights_current_distance <= straight_previous + 2.25 && rights_current_distance >= straight_previous + 1.75){ //turning 90 degreees puts the sensor about 2 inches further away from the wall it measured when looking straight
    turning = false;
    }
  }
}//end left


/*
 * Turns the rover right
 * @parm  : none
 * @return: void
 */
void roverRight(){ //ensure head is looking forward before turning
  bool turning = true;
  double straight_previous = us_sensor.measureInches();
  int iterator = 0;

  head.turnLeft();
  lefts_current_distance = us_sensor.measureInches();
  double left_previous = lefts_current_distance;

  left_motor.goForward();
  right_motor.goBackward();

  while (turning){
    lefts_current_distance = us_sensor.measureInches();
    checkRemote();
  if(lefts_current_distance <= straight_previous + 2.25 && lefts_current_distance >= straight_previous + 1.75){
    turning = false;
    }
  }
}//end right


/*
 * Makes the rover go straight
 * @parm  : none
 * @return: void
 */
void roverStraight(){
  left_motor.goForward();
  right_motor.goForward();
}//end straight


/*
 * Makes the rover go in reverse
 * @parm  : none
 * @return: void
 */
void roverReverse(){
  left_motor.goBackward();
  right_motor.goBackward();
}//end backward


/*
 * Stops the rover
 * @parm  : none
 * @return: void
 */
void roverStop(){
  left_motor.stop();
  right_motor.stop();
}//end stop

//I/O--------------------------------------------------------------------------------

/*
 * Remote controls the rover 
 * @parm  : none
 * @return: void
 */
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


/*
 * Scans foward left forward right, to use while moving. The rover slightly adjusts path
 * if it detects wall to side, checks for turns if it detects wall in front
 * @parm  : none
 * @return: void
 */
void scanDrive(){ 

      head.lookStraight();
      straights_current_distance = us_sensor.measureInches();
      checkTurn(); //immediately checks if rover needs to turn before scanning elsewhere//checks front
      checkRemote(); //
      
      head.turnLeft(); //check left -------------------------
      // measure left's current distance 
      lefts_current_distance = us_sensor.measureInches(); 
      if (lefts_current_distance < SIDE_DISTANCE_THRESHOLD) //veer right
          veerRight();

    checkRemote(); //

    head.lookStraight(); //check middle ----------------------
    straights_current_distance = us_sensor.measureInches();
    checkTurn(); //immediately checks if rover needs to turn before scanning elsewhere //checks middle in between turns

    checkRemote(); //
    head.turnRight();  //check right -------------------------
    // meausre right's current distance
    rights_current_distance = us_sensor.measureInches();  

    if(rights_current_distance < SIDE_DISTANCE_THRESHOLD) //veer left
      veerLeft();
    
     checkRemote();
     
    checkEndCourse(); //check if it has completed the course

}//end scanDrive


/*
 * Checks if the rover needs to turn then takes trhe necessary action accordingly
 * @parm  : none
 * @return: void
 */
void checkTurn(){ 
  if(straights_current_distance < (FORWARD_DISTANCE_THRESHOLD * 3)){//check if approaching wall
    
    while(straights_current_distance > FORWARD_DISTANCE_THRESHOLD){ //rover stops scanning sides and only looks forward until it is within turn range
      straights_current_distance = us_sensor.measureInches();
    }
  
        //Turn red LED on and green LED off
        digitalWrite(RED_LED,HIGH);
        digitalWrite(GREEN_LED,LOW);
        // Rover comes to a full STOP
        roverStop();
        delay(200);       
      
        if(straights_current_distance < TOO_CLOSE_THRESHOLD)
        { // If were too close to the wall
          // BACKUP 
          roverReverse();
          delay(REVERSE_DELAY);
          roverStop();
          delay(200);
        }

        straights_current_distance = us_sensor.measureInches();
        lookSides(); //look around to find which way to turn

        if(lefts_current_distance < rights_current_distance)
        {
          // We turn the rover right
          roverRight();
      
          roverStop();
          delay(100);

          roverStraight();
        }
    // else
      else
        {
          //We turn the rover left
          roverLeft();

          roverStop();
          delay(100);

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


/*
 * Scans left and right, for when car is stopped and needs to turn
 * @parm  : none
 * @return: void
 */
void lookSides(){ 
        // We need to turn the eyes left
      head.turnLeft();
      // measure left's current distance 
      lefts_current_distance = us_sensor.measureInches(); 

      head.turnRight();
      // meausre right's current distance
      rights_current_distance = us_sensor.measureInches();  

      head.lookStraight();
}


/*
 * Measures current distance from left wall and adjusts until it is in a direction heading away from it
 * @parm  : none
 * @return: void
 */
void veerRight(){
//make sure head is already facing towards LEFT 
  bool adjusting = true;
  double lefts_previous_distance = us_sensor.measureInches(); 

  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);

  right_motor.setSpeed(left_speed - 100); //starts veering left
  right_motor.goForward(); // must call the goForward functions again so they run with the new speed
  left_motor.goForward();

  while(adjusting){
  lefts_current_distance = us_sensor.measureInches();
  checkRemote();
  if(lefts_current_distance >= lefts_previous_distance + 0.5)
    adjusting = false;

  }

  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed); //resume straight path
  left_motor.goForward(); 
  right_motor.goForward();

  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RED_LED,LOW);
}//end veerRight


/*
 * Measures current distance from right wall and adjusts until it is in a direction heading away from it
 * @parm  : none
 * @return: void
 */
void veerLeft(){
//make sure head is already facing towards right
  bool adjusting = true;
  double rights_previous_distance = us_sensor.measureInches(); 

  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);

  left_motor.setSpeed(left_speed - 100); //starts veering left
  left_motor.goForward(); // must call the goForward functions again so they run with the new speed
  right_motor.goForward();

  while(adjusting){
  rights_current_distance = us_sensor.measureInches();
  checkRemote();
  if(rights_current_distance >= rights_previous_distance + 0.5)
    adjusting = false;

  }

  left_motor.setSpeed(left_speed);
  right_motor.setSpeed(right_speed); //resume straight path
  left_motor.goForward(); 
  right_motor.goForward();

  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RED_LED,LOW);
}//end veerLeft


/*
 * Checks if the rover has completed the maze by checking if distances
 * to the front, left, and right are greater than 4 feet (if this is true
 * there is no more maze left)
 * @parm  : none
 * @return: void
 */
void checkEndCourse(){

  //check that all distances are > 4 feet;
  bool rightClear = (rights_current_distance >= 4.0 * 12.0);
  bool leftClear = (lefts_current_distance >= 4.0 * 12.0);
  bool frontClear = (lefts_current_distance >= 4.0 * 12.0);

  if(rightClear && leftClear && frontClear){
    head.lookStraight();
    roverStop();
    delay(1000);
    danceParty();
  }

}//end of endCourse


/*
 * Makes the rover dance by spinning in circles and shaking back and forth
 * @parm  : none
 * @return: void
 */
void danceParty(){
  left_speed = 200;
  right_speed = 200;

  while(true){
  left_motor.goForward();
  right_motor.goBackward(); //spin right
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RC_LED,HIGH);
  delay(1500);


  roverStraight(); //MOVE IT MOVE IT
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RC_LED,LOW);
  delay(300);

  roverReverse();
  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RC_LED,LOW);
  delay(300);

  roverStraight();
  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RC_LED,HIGH);
  delay(300);

  roverReverse();
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RC_LED,LOW);
  delay(300);


  left_motor.goBackward();
  right_motor.goForward(); //spin left
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RC_LED,HIGH);
  delay(1500);

  roverStraight(); //MOVE IT MOVE IT (again)
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RC_LED,LOW);
  delay(300);

  roverReverse();
  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RC_LED,LOW);
  delay(300);

  roverStraight();
  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RC_LED,HIGH);
  delay(300);

  roverReverse();
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RC_LED,LOW);
  delay(300);

  for(int i = 1; i <5; i++) //shake ya booty (5 times)
    {
      left_motor.goBackward();
      right_motor.goForward();
      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);

      delay(200);

      left_motor.goForward();
      right_motor.goBackward(); 
      digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,HIGH);
      delay(200);
    }
  }
} // end danceParty