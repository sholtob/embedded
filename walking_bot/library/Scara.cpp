/*

*/

#include <Arduino.h>
#include <Scara.h>

#include <Servo.h>
#include <math.h>

// Define the lengths of leg segments squared for inverse kinematics:
#define L1 20
#define L2 30


Scara::Scara(int frontServoPin, int backServoPin)
  {  
  _frontServoPin = frontServoPin;
  _backServoPin = backServoPin;
}  

void Scara::init() {
  _servoA.attach(_frontServoPin);
  _servoB.attach(_backServoPin);
  posA = 45;
  posB = 135;
  radius = 30; //Sets legs initial length.
  theta = 90; // Sets leg inital angle in degrees.
}

void Scara::angleAWrite(int thetaA) {
  /* takes angle theta referenced to horizon, 
   * then transforms it to frame of servoA and sends. 
   */
   int posFrame = thetaA + 45;
   if (posFrame > 0 && posFrame < 170 && posB - posA > 20) { 
      _servoA.write(posFrame);
   }
   else { 
      Serial.print(thetaA);
      Serial.println(" is outside of allowed servo A range.");
   }
}

void Scara::angleBWrite(int thetaB) {
  /* takes angle theta referenced to horizon, 
   * then transforms it to frame of servoB and sends. 
   */
   int posFrame = 225 - thetaB;
   if (posFrame > 0 && posFrame < 170 && posB - posA > 20) {
      _servoB.write(posFrame);
      Serial.println(posFrame);
   }
   else { 
      Serial.print(thetaB);
      Serial.println(" is outside of allowed servo B range.");
   }
}

void Scara::legWrite() {
  /* Moves the servos to the positions stored
   * in posA and posB
   */
  angleAWrite(posA);
  angleBWrite(posB);
}

void Scara::legAngle(int angle) {
  /* This sets the angle of imaginary line 
   *connecting motor axles to foor pivot.
   * Theta referenced to robot body horizontal plane.
   */
   int legOffset = int(round(float((posB - posA)/2.)));
   //Should only update posA if position actually reachable.
   posA = angle - legOffset;
   posB = angle + legOffset;
   //angleAWrite(posA);
   //angleBWrite(posB);
}

void Scara::legLength(int rad) {
  
  int gamma = int(round(acos(float((L1*L1 - L2*L2 +rad*rad))/float((2*L1*rad)))*180./M_PI));
  //Serial.print("gamma ");
  //Serial.println(acos(float((L1*L1 - L2*L2 +rad*rad))/float((2*L1*rad))));
  posA = theta - gamma;
  posB = theta + gamma;
  //angleAWrite(posA);
  //angleBWrite(posB);
}


