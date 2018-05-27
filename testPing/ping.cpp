/*
  Test.h - Basic ping sensor library - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

#include "Arduino.h"

// include this library's description file
#include "ping.h"

// include description files for other libraries used (if any)

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Ping::begin(int trigP, int echoP)
{
  // initialize this instance's variables
  trigPin = trigP;
  echoPin = echoP;

  // do whatever is required to initialize the library
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

int Ping::readDistance(void)
{
  long pulseLength;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pulseLength = pulseIn(echoPin, HIGH, PING_TIMEOUT_US);

  return (int)(pulseLength / HCSRO4_US_TO_CM_DIVISOR);
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

