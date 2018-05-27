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

  cm = ping.readDistance();

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}
