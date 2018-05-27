#include "ping.h"

#define FORWARD_SPEED 10

#define LEFT_SERVO_HUG_POS 90
#define RIGHT_SERVO_HUG_POS 90
#define LEFT_SERVO_RELEASE_POS 0
#define RIGHT_SERVO_RELEASE_POS 0

static int triggerPin = 12;
static int echoPin = 11;
static int motorPwmPin;
static int leftMotorDirPin;
static int rightMotorDirPin;
static int leftServoPin;
static int rightServoPin;

Ping ping;
motors motorObj;

Servo leftServo;
Servo rightServo;

void setup() {
  ping.begin(triggerPin, echoPin);
  motorObj.motors(motorPwmPin, leftMotorDirPin, rightMotorDirPin);
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
}

void loop() {
  //Check for a hand

  if(ping.distanceFilter()) {
    motorObj.motor_cmd(FORWARD_SPEED);
    
    delay(1000);

    motorObj.motor_cmd(0);
    servo_hug();

    delay(500);

    //Play audio clip

    servo_release();
  }
  else {
    delay(100);
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
