/* 
Controls the position of a hobby servo on pin 8 with serial signals.

*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int sIn = 90; //stores serial position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  sIn = Serial.parseInt();
  Serial.println(sIn);
  if (sIn != 0) pos = sIn;
  myservo.write(pos);
}
