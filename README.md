 # Rover Robot
<b>Main file: </b> Rover.ino 
<br> <b> Group Members: </b> David Betanzos and William Dragstrem </br>
<p> The goal of this project is to make a rover navigate a course maze in C++ using Arduino and AVR libraries. The width of the course is roughly 28 inches apart and  6 inches high. </p>

<img src = "https://content.arduino.cc/assets/arduino_logo_1200x630-01.png">

## States Used
 <p>The rover has 6 main states: moving, stopped, turning (left or right), veering, remote controlled, and dancing.</p>

<br> <b> Moving </b> : The rover moves forward while constantly rotating its head and measuring the distance to forward, left, forward, right, in that order on repeat. If it detects a wall straight ahead within about 3 feet. It stops scanning the sides and continues forward until it is within the turning threshold distance. It then enters the stopped state. If it does not detect a wall ahead but it detects it is too close to a wall on the right or left side, it enters the veering state. The robot also checks at the end of the loop if it is outside the course, in which case it enters the Dancing state. 
<br>

<br> <b>Stopped</b>:  If the rover is too close to the wall in front of it, it backs up to an acceptable distance to turn. Regardless, it then scans to its left and its right to determine which direction has the greater distance and determines that to be the direction in which it needs to turn. It then enters the Turning state. 
 </br>

 <br> <b>Turning</b>:  (Substates: left/right) Say the robot is turning right, it measures the distance between the rover and the wall currently straight ahead of it. Then it turns its head left and spins clockwise, continuously measuring the distance in front of the head. The robot continues to spin until it measures the same distance as what was once in front of it (plus about 2 inches to account for the distance offset when looking to the side rather than forward), indicating the wall that was once in front of it is now 90 degrees to its left, which means the robot has turned 90 degrees to the right. Once this is satisfied, it enters the moving state again. 
 </br>

  <br> <b>Veering</b>: If the rover gets too close to a wall in the course. The robot spins in place until its head is a marginal distance further (0.4 inches) from the wall. This was determined experimentally to veer the robot just enough from the wall it sets it on course towards the center of the path.
 </br>

 
  <br> <b>Remote Controlled</b>: Rover is remote controlled by the IR remote and a yellow LED will light on. We transition to this state if we press the power button on the IR remote (this would only occur if we see that the rover clearly got stuck in the course). The remote only controls basic functionality needed by the rover such as making the rover go left, right, backwards, and forwards. If we press the power button again, we exit the remote controlled state and go to the scan drive state.
 </br>


   <br> <b>Dancing</b>: Rover performs a little dance then follows by moving back and forth between left and right. We transition to this state if the rover measures the left, right, and forwards distance to a minimum of 6 feet or more. At this point, the rover is done with the course since there are no more walls surrounding it.
 </br>

 ## Arduino Features Used

<p> IR remote, ultrasonic sensor, servo, DC motors, LED's </p>

