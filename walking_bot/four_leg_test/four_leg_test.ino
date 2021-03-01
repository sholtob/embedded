#include <Scara.h>
#include <math.h>

#define DEL 500
#define N 20 // number of points foot moves to in each leg portion.

Scara frontLeft(9, 8);
Scara frontRight(7, 6);
Scara backLeft(5, 4);
Scara backRight(3, 2);


int sIn = 90; //stores serial position


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  frontLeft.init();
  frontRight.init();
  backLeft.init();
  backRight.init();

}

void loop() {
  // put your main code here, to run repeatedly:

}
