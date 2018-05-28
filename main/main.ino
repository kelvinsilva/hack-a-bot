#include "ping.h"
#include "motors.h"
#include <Servo.h>
#include "ToneGeneration.h"
#include "PatRead.h"

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

#define SPEAKER_PIN 9
#define PAT_PIN_1 2
#define PAT_PIN_2 3
#define HAPPY_LENGTH 9
#define L2 2


#define DRIVE_FWD_TIME 2000
#define HUG_TIME 1000
#define HUG_RELEASE_TIME 500
#define DRIVE_BACK_TIME 2000

#define PING_RECHECK_TIME 100

#define ECHO_PIN 11
#define TRIGGER_PIN 12


unsigned int happy[HAPPY_LENGTH][2]={
  {100, 45+15},
  {100, 47+15},
  {100, 49+15},
  {100, 51+15},
  {100, 53+15},
  {200, 0},
  {150, 54+15},
  {100, 0},
  {150, 54+15},
  }; 

unsigned int twoTone[L2][2]={
  {2, 47},
  {2, 47+8}
  };

Ping ping_sensor;
Servo leftServo;
Servo rightServo;
unsigned long int curTime;
bool stopMusic = true;

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
  
  curTime = millis();

  ping_sensor.begin(TRIGGER_PIN, ECHO_PIN);
  // motorObj.motors(motorPwmPin, leftMotorDirPin, rightMotorDirPin);
  leftServo.attach(LEFT_SERVO_PIN); //digital pins
  rightServo.attach(RIGHT_SERVO_PIN);

  // Translate happy to frequencies
  for(int i = 0; i < HAPPY_LENGTH; i++){
      happy[i][1] = getPianoFreq(happy[i][1]);
    }
}

// 1 for move forward for 2 secs, hug, and back
// 2 for pat recieved, play sound and hug
static int state = 0;


void loop() {
  bool startPat = false;
  curTime = millis();

  // put your main code here, to run repeatedly
  if(wasPat(PAT_PIN_1, PAT_PIN_2)){
      Serial.println("Pat receieved.");
      stopMusic = false;
      startPat = true;
    }
  int index = makeTone(SPEAKER_PIN, happy, HAPPY_LENGTH, curTime, stopMusic);
  if(index == 0 && !startPat){
      stopMusic = true;
    }

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
