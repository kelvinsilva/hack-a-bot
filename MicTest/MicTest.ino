#include "./Lib/MicRead.h"
#include "./Lib/MicRead.c"

#define MIC_PIN A7

unsigned long int curTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("start\n");
  curTime = millis();
  
}

void loop() {
  // put your main code here, to run repeatedly
  curTime = millis();
  //micState = checkMic(curTime);
  delay(10);
  int val = analogRead(MIC_PIN);
  Serial.println(val);
  if(val < 730){
      Serial.println("Sound!");
    }
}
