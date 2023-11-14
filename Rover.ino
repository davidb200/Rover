/*
* The main application
*/

// Interrupts notes
// In Loop
// if (need turn head left)
    // init head_turn counter
    //
  ////////
  // IN ISR
  // If (head_turn_counter)
    // -- head turn counter
////////////////////////////

#include "UltrasonicSensor.h"
#include "MyServo.h"
#include "Motor.h"
#include "Remote.h"
#include "Robot.h"

// Constants
// LED's
const byte RED_LED           = A4;
const byte GREEN_LED         = A5;

// Global variables

// Wheels

// Ultrasonic sensor
UltrasonicSensor us_sensor(TRIGGER_PIN,ECHO_PIN);
double current_distance;

// Servo
bool servo_is_turning = false;
// Motors

void setup(){
  // LED's 
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,HIGH);
  // Ultrasonic Sensor
  Serial.begin(9600);
  us_sensor.setupTimer1();

  // Servo

  // Motors
  
}

bool do_measurement = false;

void loop(){

  // Take a measurement
  if(do_measurement)
  {
    Serial.print("Distance:");
    current_distance = us_sensor.measureInches();
    Serial.println(current_distance);
    do_measurement = false;
  }

  // Here we check if the current distance is less than the tolerable distance
      // If true
        // Rover comes to a full STOP
        // We need to turn the eyes left
        // measure left's current distance 
        // Then turn the eyes right
        // meausre right's current distance
        // If left's current distance is less than right's current distance
          // We turn the rover right
        // else
          // We turn the rover left
      // else 
        // We keep the eyes straight      
        // Move the rover forward
}

ISR(TIMER1_OVF_vect) {
  Serial.println("ISR happening");
  do_measurement = true;
  TCNT1 = TM1_COUNT; // reset the counter
 } 