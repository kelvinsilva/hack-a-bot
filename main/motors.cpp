#include "motors.h"
#include <arduino.h>

static int motorState = 0;

// 1 for forward by one step, -1 backward for one step, 0 for stop, 2 left, 3 right
void motorForwardBack(int a){

  if (motorState != a){ //only if input state is different than current state, then update pins.
    //reason for this is if in the loop we call motorControl(1) repeatedly, motor library wont work. if constantly setting the pins in the loop, motor wont work.
    switch( a){

      case 1:{ // 1) Fast forward
        // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );

        digitalWrite( MOTOR_A_DIR, LOW);
        digitalWrite( MOTOR_A_PWM, LOW);

        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_B_PWM, 255-PWM_FAST ); // PWM speed = fast

        digitalWrite(MOTOR_A_DIR, HIGH);
        analogWrite(MOTOR_A_PWM, 255-PWM_FAST);
        motorState = 1;
      }
      break;

      case -1:{ // 5) Fast reverse

        // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );

        digitalWrite( MOTOR_A_DIR, LOW);
        digitalWrite( MOTOR_A_PWM, LOW);
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
        analogWrite( MOTOR_B_PWM, PWM_FAST ); // PWM speed = fast

        digitalWrite( MOTOR_A_DIR, LOW);
        analogWrite( MOTOR_A_PWM, PWM_FAST);
        motorState = -1;
      }
      break;

      default:  // default stops
      case 0:{ // 3) Soft stop (preferred)

        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );

        digitalWrite( MOTOR_A_DIR, LOW );
        digitalWrite( MOTOR_A_PWM, LOW );
        motorState = 0;
      }
      break;
    }
  }
}
