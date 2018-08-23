/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    

void setup() {
  myservo.attach(3);  // attaches the servo on pin 3 
  myservo.write(90);  // set the servo to its middle (head must be in the middle when idle)

}

void loop() {
  for (int i = 45; i >= 10 ; i -= i / 5) { //some math to exponentially decrease head's angle of deviation
    for (pos = 90; pos <= 90 + i; pos += 1) { //turn left 
      myservo.write(pos);              
      delay(5);                       
    }
    for (pos = 90 + i; pos >= 90 - i; pos -= 1) { //tu rn right
      myservo.write(pos);              
      delay(5);                       
    }
    for (pos = 90 - i; pos <= 90; pos += 1) { //come back to center
      myservo.write(pos);              
      delay(5);                       
    }
  }
}

