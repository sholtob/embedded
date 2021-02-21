/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <math.h>

// Define the lengths of leg segments squared for inverse kinematics:
#define L1 20
#define L2 30

Servo servoA;  // create servo object to control a servo
Servo servoB;
// twelve servo objects can be created on most boards


int posA = 35;    // variable to store the servo position
int posB = 145;
int theta = 90;
int radius = 37; //mm


int sIn = 90; //stores serial position

void setup() {
  Serial.begin(9600);
  servoA.attach(9);  // attaches the servo on pin 9 to the servo object
  servoB.attach(8);

}

void loop() {
  sIn = Serial.parseInt();
  Serial.println(sIn);
  if (sIn != 0) {
    radius = sIn;
    legLengthWrite(radius);
  }
}

void angleAWrite(int thetaA) {
  /* takes angle theta referenced to horizon, 
   * then transforms it to frame of servoA and sends. 
   */
   int posFrame = thetaA + 45;
   if (posFrame > 0 && posFrame < 170 && posB - posA > 20) { // Needs to take into account position of servo B.
      servoA.write(posFrame);
   }
   else { 
      Serial.print(thetaA);
      Serial.println(" is outside of allowed servo A range.");
   }
}

void angleBWrite(int thetaB) {
  /* takes angle theta referenced to horizon, 
   * then transforms it to frame of servoB and sends. 
   */
   int posFrame = 225 - thetaB;
   if (posFrame > 0 && posFrame < 170 && posB - posA > 20) { // Needs to take into account position of other servo.
      servoB.write(posFrame);
   }
   else { 
      Serial.print(thetaB);
      Serial.println(" is outside of allowed servo B range.");
   }
}

void legAngleWrite(int angle) {
  /* This sets the angle of imaginary line 
   *connecting motor axles to foor pivot.
   * Theta referenced to robot body horizontal plane.
   */
   int legOffset = int(round(float((posB - posA)/2.)));
   posA = angle - legOffset;
   posB = angle + legOffset;
   angleAWrite(posA);
   angleBWrite(posB);
}

void legLengthWrite(int rad) {
  
  int gamma = int(round(acos(float((L1*L1 - L2*L2 +rad*rad))/float((2*L1*rad)))*180./M_PI));
  //Serial.print("gamma ");
  //Serial.println(acos(float((L1*L1 - L2*L2 +rad*rad))/float((2*L1*rad))));
  posA = theta - gamma;
  posB = theta + gamma;
  angleAWrite(posA);
  angleBWrite(posB);
}
