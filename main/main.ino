#include "ping.h"
#include "motors.h"
#include <Servo.h>

#define BAUD_RATE 9600
#define FORWARD_SPEED 10
#define REVERSE_SPEED

//servo setup
#define LEFT_SERVO_HUG_POS 90
#define RIGHT_SERVO_HUG_POS 90
#define LEFT_SERVO_RELEASE_POS 0
#define RIGHT_SERVO_RELEASE_POS 0
#define LEFT_SERVO_PIN 4    //  D4, All digital write
#define RIGHT_SERVO_PIN 5   // D5


#define DRIVE_FWD_TIME 2000
#define HUG_TIME 1000
#define HUG_RELEASE_TIME 500
#define DRIVE_BACK_TIME 2000

#define PING_RECHECK_TIME 100

#define ECHO_PIN 11
#define TRIGGER_PIN 12


Ping ping_sensor;
Servo leftServo;
Servo rightServo;

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

  ping_sensor.begin(TRIGGER_PIN, ECHO_PIN);
  // motorObj.motors(motorPwmPin, leftMotorDirPin, rightMotorDirPin);
  leftServo.attach(LEFT_SERVO_PIN); //digital pins
  rightServo.attach(RIGHT_SERVO_PIN);
}

// 1 for move forward for 2 secs, hug, and back
// 2 for pat recieved, play sound and hug
static int state = 0;


void loop() {

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
    //return to original position
    motorForwardBack(-1);
    delay(DRIVE_BACK_TIME);
    motorForwardBack(0);
    

  }
 /*do pat sensor 
  servo_hug();
    //PlayAudio
    delay(HUG_TIME);
    servo_release();
  }*/
}

void servo_hug(void) {
  leftServo.write(LEFT_SERVO_HUG_POS);
  rightServo.write(RIGHT_SERVO_HUG_POS);
}

void servo_release(void) {
  leftServo.write(LEFT_SERVO_RELEASE_POS);
  rightServo.write(RIGHT_SERVO_RELEASE_POS);
}
