
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
  stride(30., 25., 0.1);


}
float cartToRad(float x, float y) {
  //Converts cartesian x, y coords to polar radius.
  return sqrt(x*x + y*y);
}

float cartToTheta(float x, float y) {
  // Converts cartesian x, y coordinates to polar angle.
  // +x is in front of the hip joint, +y is below it.
  return atan2(y, x)*180./M_PI;
}
void stride(float l, float h, float v) {
  /* l is distance over which the foot touches the floor, 
   * h is height of robot above the floor,
   * v is robots velicity.
   */
   int T = int(l/(N*v));
   int angle = 90;
   float radius = h;
   
   // Foot on floor portion:
   // y is constant, equal to h
   for (int i=0; i<N; i++) {
    float x = l/2. - i*l/N;
    angle = int(round(cartToTheta(x, h)));
    radius = cartToRad(x, h);
    sc.movePolar(radius, angle);
//    Serial.print("angle ");
//    Serial.println(angle);
//    Serial.print("radius ");
//    Serial.println(radius);
    delay(T);
   }
   
  //raise foot so it leaves the ground by reducing radius
  radius -= 5;
  sc.movePolar(radius, angle);
  delay(T);

  // move back to centre of travel
  sc.movePolar(15, 90);
  delay (200);

}
/*
void serLenWrite() {
  sIn = Serial.parseInt();
  Serial.println(sIn);
  if (sIn != 0) {
    int radius = sIn;
    sc.legAngle(radius);
    sc.legWrite();
  }
  Serial.print("posA");
  Serial.println(sc.posA);
  Serial.print("posB");
  Serial.println(sc.posB);
}


void loop() {
  sc.angleAWrite(0);
  sc.angleBWrite(100);
  Serial.println("big");
  delay(2000);
  sc.angleAWrite(90);
  sc.angleBWrite(150);
  Serial.println("small");
  delay(2000);
}
*/
