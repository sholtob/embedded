
#include <Scara.h>

Scara sc(9, 8);

int sIn = 90; //stores serial position


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sc.init();

}


void loop() {
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
/*

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
