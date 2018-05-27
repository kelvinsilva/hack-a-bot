/*
  HG7881_Motor_Driver_Example - Arduino sketch
   
  This example shows how to drive a motor with using HG7881 (L9110) Dual
  Channel Motor Driver Module.  For simplicity, this example shows how to
  drive a single motor.  Both channels work the same way.
   
  This example is meant to illustrate how to operate the motor driver
  and is not intended to be elegant, efficient or useful.
   
  Connections:
   
    Arduino digital output D10 to motor driver input B-IA.
    Arduino digital output D11 to motor driver input B-IB.
    Motor driver VCC to operating voltage 5V.
    Motor driver GND to common ground.
    Motor driver MOTOR B screw terminals to a small motor.
     
  Related Banana Robotics items:
   
    BR010038 HG7881 (L9110) Dual Channel Motor Driver Module
    https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 
  https://www.BananaRobotics.com
*/
 
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



static int motorState = 0;
 //1 for forward by one step, -1 backward for one step, 0 for stop, 2 left, 3 right
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

void setup()
{
  Serial.begin( 9600 );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );

  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  digitalWrite(MOTOR_A_DIR, LOW);
  digitalWrite(MOTOR_A_PWM, LOW);
  
}


void loop()
{

  motorForwardBack(0);
}
/*EOF*/
