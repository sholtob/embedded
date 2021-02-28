
#include <Scara.h>
#include <math.h>

#define DEL 500
#define N 20 // number of points foot moves to in each leg portion.

Scara sc(9, 8);

int sIn = 90; //stores serial position


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sc.init();

}

void loop() {
  Serial.println("loop");
  sc.initStride(40, 35., 0.2);
  sc.stride();

}                                                                              
