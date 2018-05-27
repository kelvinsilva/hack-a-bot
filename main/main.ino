#include "ping.h"

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
    //Move forward
    motorObj.motor_cmd(FORWARD_SPEED);
    delay(DRIVE_FWD_TIME);
    motorObj.motor_cmd(0);

    //Hug
    servo_hug();
    //Play audio clip
    delay(HUG_TIME);
    servo_release();
    delay(HUG_RELEASE_TIME);

    //Return to original position
    motorObj.motor_cmd(REVERSE_SPEED);
    delay(DRIVE_BACK_TIME);
    motorObj.motor_cmd(0);
  }
  else {
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
