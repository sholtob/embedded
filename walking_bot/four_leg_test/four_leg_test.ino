#include <Scara.h>
#include <math.h>

#define DEL 500
#define N 100 // number of points foot moves to in each leg portion.

#define L 40
#define H 40
#define V 0.4

Scara frontLeft(8, 9);
Scara frontRight(7, 6);
Scara backLeft(4, 5);
Scara backRight(3, 2);


int sIn = 90; //stores serial position


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  frontLeft.init();
  frontRight.init();
  backLeft.init();
  backRight.init();
  
  pinMode(LED_BUILTIN, OUTPUT);

  flash_LED();
  frontLeft.initStride(L, H, V);
  frontRight.initStride(L, H, V);
  backLeft.initStride(L, H, V);
  backRight.initStride(L, H, V);

  flash_LED();
}
byte s = 0;
void loop() {
  //walk();
  Serial.println(s);
  s+=1;
}

void walk() {
//  int fL = 62;
//  int fR = 12;
//  int bL = 0;
//  int bR = 52;

//trot
  int fL = 50;
  int fR = 0;
  int bL = 0;
  int bR = 50;

  
  while (1) {
     frontLeft.strideStep(fL);
     fL += 1;
     if (fL>N*1.2) fL = 0;
     
     frontRight.strideStep(fR);
     fR += 1;
     if (fR>N*1.2) fR = 0;
     
     backLeft.strideStep(bL);
     bL += 1;
     if (bL>N*1.2) bL = 0;
     
     backRight.strideStep(bR);
     bR += 1;
     if (bR>N*1.2) bR = 0;

     delay(frontLeft._T);
     
  }
}




void flash_LED() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW 
}
