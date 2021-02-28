/*

*/

#include <Arduino.h>
#include <Scara.h>

#include <Servo.h>
#include <math.h>

// Define the lengths of leg segments squared for inverse kinematics:
#define L1 23.
#define L2 30.
#define N 200 // number of points foot position calculated at. 
#define WALK_T 100 // times between large walk distances.

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

void Scara::initStride(float l, float h, float v) {
 /* calculates variables needed when robot takes a step.
  * l is distance over which the foot touches the floor, 
  * h is height of robot above the floor,
  * v is robots velocity.
  */
  _T = int(round(l/(N*v)));
  _h = h;
  _dPerStep = l/N;
  _lOn2 = l/2;
  _angle0 = int(round(cartToTheta(_lOn2, h-10))); //y part might not be high enough if h is small.
  _rad0 = cartToRad(_lOn2, h-10);
}

void Scara::stride() {
  /* A step is taken each time this function is called.
  */
  movePolar(_rad0, _angle0);
  delay(WALK_T);
  // Foot on floor portion:
  // y is constant, equal to h
  for (int i=0; i<N; i++) {
   float x = _lOn2 - i*_dPerStep;
   theta = int(round(cartToTheta(x, _h)));
   radius = cartToRad(x, _h);
   movePolar(radius, theta);
//    Serial.print("angle ");
//    Serial.println(angle);
//    Serial.print("radius ");
//    Serial.println(radius);
    delay(_T);
   }
   
  //raise foot so it leaves the ground by reducing radius
  radius -= 4;
  movePolar(radius, theta);
  delay(WALK_T/5);

  // move back to centre of travel
  movePolar(15, 90);
  delay(WALK_T);
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
      //Serial.println(posFrame);
   }
   else { 
      Serial.print(thetaB);
      Serial.println(" is outside of allowed servo B range.");
   }
}

void Scara::movePolar(float rad, int angle) {
  /* Moves the servos to the positions stored
   * in posA and posB
   */
  radius = rad;
  theta = angle;

  //Calculate motor positions for given leg radius:
  legLength(radius);
  // Calculate motor positions so leg has given angle:
  legAngle(angle);

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

void Scara::legLength(float rad) {
  
  int gamma = int(round(acos((L1*L1 - L2*L2 +rad*rad)/(2.*L1*rad))*180./M_PI));
  //Serial.print("gamma ");
  //Serial.println(acos(float((L1*L1 - L2*L2 +rad*rad))/float((2*L1*rad))));
  posA = theta - gamma;
  posB = theta + gamma;
  //angleAWrite(posA);
  //angleBWrite(posB);
}

float Scara::cartToRad(float x, float y) {
  //Converts cartesian x, y coords to polar radius.
  return sqrt(x*x + y*y);
}

float Scara::cartToTheta(float x, float y) {
  // Converts cartesian x, y coordinates to polar angle.
  // +x is in front of the hip joint, +y is below it.
  return atan2(y, x)*180./M_PI;
}
