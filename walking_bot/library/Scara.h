/*

*/

#ifndef Scara_h
#define Scara_h 

#include "Arduino.h"
#include <Servo.h>

class Scara
{
  public:
    Scara(int frontServoPin, int backServoPin);
    void init();
    void angleAWrite(int thetaA);
    void angleBWrite(int thetaB);
    void legWrite();
    void legAngle(int angle);
    void legLength(int rad);
    int posA;
    int posB;
    int radius;
    int theta;
  private:
    Servo _servoA;
    Servo _servoB;
    int _frontServoPin;
    int _backServoPin;
};

#endif
