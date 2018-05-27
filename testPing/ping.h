/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Ping_h
#define Ping_h

#define PING_TIMEOUT_US 100000

// library interface description
class Ping
{
  // user-accessible "public" interface
  public:
    void begin(int, int);
    int readDistance(void);

  // library-accessible "private" interface
  private:
    int trigPin;
    int echoPin;
};

#endif

