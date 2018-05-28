/*
  ping.h - Basic ping sensor library - implementation
  Copyright (c) 2018 UCSC HAckabot Team 1.  All right reserved.
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

  for(int i=0; i<NUM_IN_ROW; i++)
  {
    ringBuf[i] = false;
  }

  index = 0;
  ringTotal = 0;
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

bool Ping::distanceFilter(void)
{
  int pingDistance = readDistance();

  if((pingDistance > TRUEDISTANCE) || pingDistance == 0)
  {
    if(ringBuf[index] == true)
    {
      ringTotal--;
    }
    
    ringBuf[index] = false;
  }
  else
  {
    if(ringBuf[index] == false)
    {
      ringTotal++;
    }
    
    ringBuf[index] = true;
  }

  index = (index + 1) % NUM_IN_ROW;

  if(ringTotal == NUM_IN_ROW)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

