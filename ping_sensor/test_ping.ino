#include "ping.h"

static int tPin = 12;
static int ePin = 11;

Ping ping;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  ping.begin(tPin, ePin);
}

void loop() {
  // put your main code here, to run repeatedly:

  int cm;
  bool hand;

  cm = ping.readDistance();
  hand = ping.distanceFilter();

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.print("Hand: ");
  Serial.print(hand);
  Serial.println();

  delay(100);
}
