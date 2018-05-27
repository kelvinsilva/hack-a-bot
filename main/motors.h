#ifndef MOTORS_H
#define MOTORS_H

// wired connections
#define HG7881_B_IA 14 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 15 // D11 --> Motor B Input B --> MOTOR B -

#define HG7881_A_IA 16
#define HG7881_A_IB 17

// functional connections
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction

#define MOTOR_A_PWM HG7881_A_IA // Motor A PWM Speed and Dir
#define MOTOR_A_DIR HG7881_A_IB

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 50  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 200 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

void motorForwardBack(int a);

#endif
