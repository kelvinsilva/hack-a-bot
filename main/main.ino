#include "motors.h"

#define BAUD_RATE 9600

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(MOTOR_B_DIR, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
  digitalWrite(MOTOR_B_DIR, LOW );
  digitalWrite(MOTOR_B_PWM, LOW );

  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  digitalWrite(MOTOR_A_DIR, LOW);
  digitalWrite(MOTOR_A_PWM, LOW);

}


void loop() {
  // State machine loop goes here
  motorForwardBack(0);
}

