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
    void movePolar(float radius, int theta);
    void legAngle(int angle);
    void legLength(float rad);
    void initStride(float l, float h, float v);
    void stride();
    float cartToRad(float x, float y);
    float cartToTheta(float x, float y);
    int posA;
    int posB;
    float radius;
    int theta;

  private:
    Servo _servoA;
    Servo _servoB;
    int _frontServoPin;
    int _backServoPin;
    int _T; // Time taken to go between each calculated point in walk cycle.
    float _dPerStep; //Distance between each calculated point n walk cycle.
    float _h; // length of leg when foot is on the floor.
    int _angle0; //angle of leg just before foot touches the floor.
    int _rad0 // length of leg just before foot touches the floor.
};

#endif
