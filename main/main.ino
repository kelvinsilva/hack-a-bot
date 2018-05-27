#include <Servo.h>

#define SERVO_PIN 5

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}

void loop() {
//  myservo.write(45);                  // sets the servo position according to the scaled value
  delay(500);                           // waits for the servo to get there
//  myservo.write(120);
  delay(500);
}

