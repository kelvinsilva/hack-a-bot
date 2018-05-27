#include "ping.h"
#include "motors.h"
#include <Servo.h>

#define FORWARD_SPEED 10
#define REVERSE_SPEED

#define LEFT_SERVO_HUG_POS 90
#define RIGHT_SERVO_HUG_POS 90
#define LEFT_SERVO_RELEASE_POS 0
#define RIGHT_SERVO_RELEASE_POS 0

#define DRIVE_FWD_TIME 1000
#define HUG_TIME 1000
#define HUG_RELEASE_TIME 500
#define DRIVE_BACK_TIME 1000

#define PING_RECHECK_TIME 100

#define ECHO_PIN 11
#define TRIGGER_PIN 12
static int motorPwmPin;
static int leftMotorDirPin;
static int rightMotorDirPin;
static int leftServoPin;
static int rightServoPin;

Ping ping_sensor;
Servo leftServo;
Servo rightServo;

void setup() {
  // Motor Setup
  pinMode(MOTOR_B_DIR, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
  digitalWrite(MOTOR_B_DIR, LOW );
  digitalWrite(MOTOR_B_PWM, LOW );

  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  digitalWrite(MOTOR_A_DIR, LOW);
  digitalWrite(MOTOR_A_PWM, LOW);

  ping_sensor.begin(TRIGGER_PIN, ECHO_PIN);
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
}

void loop() {
  // Check for a hand

  if(ping_sensor.distanceFilter()) {
    // Move forward
    motorForwardBack(1);
    delay(DRIVE_FWD_TIME);
    motorForwardBack(0);

    // Hug
    servo_hug();
    // Play audio clip
    delay(HUG_TIME);
    servo_release();
    delay(HUG_RELEASE_TIME);

    // Return to original position
    motorForwardBack(-1);
    delay(DRIVE_BACK_TIME);
    motorForwardBack(0);

  } else {
    delay(PING_RECHECK_TIME);
  }
}

void servo_hug(void) {
  leftServo.write(LEFT_SERVO_HUG_POS);
  rightServo.write(RIGHT_SERVO_HUG_POS);
}

void servo_release(void) {
  leftServo.write(LEFT_SERVO_RELEASE_POS);
  rightServo.write(RIGHT_SERVO_RELEASE_POS);
}
