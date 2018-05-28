#include "./Lib/ToneGeneration.h"
#include "./Lib/ToneGeneration.c"
#include "./Lib/PatRead.h"
#include "./Lib/PatRead.c"

#define SPEAKER_PIN 9
#define PAT_PIN_1 2
#define PAT_PIN_2 3
#define HAPPY_LENGTH 9
#define L2 2

unsigned int happy[HAPPY_LENGTH][2]={
  {100, 45+15},
  {100, 47+15},
  {100, 49+15},
  {100, 51+15},
  {100, 53+15},
  {200, 0},
  {150, 54+15},
  {100, 0},
  {150, 54+15},
  }; 

unsigned int twoTone[L2][2]={
  {2, 47},
  {2, 47+8}
  };

unsigned long int curTime;
boolean stopMusic = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("start\n");
  curTime = millis();

  for(int i = 0; i < HAPPY_LENGTH; i++){
      happy[i][1] = getPianoFreq(happy[i][1]);
    }
}

void loop() {
  boolean startPat = false;
  curTime = millis();
  
  // put your main code here, to run repeatedly
  if(wasPat(PAT_PIN_1, PAT_PIN_2)){
      Serial.println("Pat receieved.");
      stopMusic = false;
      startPat = true;
    }
  int index = makeTone(SPEAKER_PIN, happy, HAPPY_LENGTH, curTime, stopMusic);
  if(index == 0 && !startPat){
      stopMusic = true;
    }
}
