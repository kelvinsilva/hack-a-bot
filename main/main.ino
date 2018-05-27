#include "motors.h"
#include "ping.h"

#define BAUD_RATE 9600

// Ping Setup
#define ECHO_PIN 11
#define TRIGGER_PIN 12
Ping ping_sensor;


void setup() {
  Serial.begin(BAUD_RATE);

  // Motor Setup
  pinMode(MOTOR_B_DIR, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
  digitalWrite(MOTOR_B_DIR, LOW );
  digitalWrite(MOTOR_B_PWM, LOW );

  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  digitalWrite(MOTOR_A_DIR, LOW);
  digitalWrite(MOTOR_A_PWM, LOW);

  // Ping Setup
  ping_sensor.begin(TRIGGER_PIN, ECHO_PIN);  

}


void loop() {
  // State machine loop goes here
  //  motorForwardBack(0);
  if (ping.distanceFilter()) {
    // You see a hand, do some stuff
  }
}

