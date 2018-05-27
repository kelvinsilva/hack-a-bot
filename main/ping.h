/*
  ping.h - Basic ping sensor library - implementation
  Copyright (c) 2018 UCSC Hackabot Team 1. All right reserved.
*/

// ensure this library description is only included once
#ifndef PING_H
#define PING_H

#define PING_TIMEOUT_US 100000

#define HCSRO4_US_TO_CM_DIVISOR 58

#define TRUEDISTANCE 35
#define NUM_IN_ROW 3

// library interface description
class Ping
{
  // user-accessible "public" interface
  public:
    //Begin: Input trig pin, echo pin
    void begin(int, int);

    //readDistance: returns distance in cm
    int readDistance(void);

    //distanceFilter: Executes a ping, Returns TRUE if the last NUM_IN_ROW pings were within TRUEDISTANCE.
    bool distanceFilter(void);

  // library-accessible "private" interface
  private:
    int trigPin;
    int echoPin;
    bool ringBuf[NUM_IN_ROW];
    int index;
    int ringTotal;
};

#endif

