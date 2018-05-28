#include "./Lib/ToneGeneration.h"
#include "./Lib/ToneGeneration.c"

#define SPEAKER_PIN 9
#define TONES_LENGTH 2
#define KEYS_LENGTH 8

unsigned long int curTime, toneTime;

// Tones
unsigned int tones[TONES_LENGTH][2] = {
  {1000, 1000}, 
  {500, 2000},
  };

unsigned int keys[KEYS_LENGTH][2]={
  {1000, 45},
  {1000, 46},
  {1000, 47},
  {1000, 48},
  {1000, 49},
  {1000, 48},
  {1000, 47},
  {1000, 46}
  };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("start");
  curTime = millis();
  toneTime = curTime;

  // Convert keys to freqs
  for(int i = 0; i < KEYS_LENGTH; i++){
      Serial.println(keys[i][1]);
      keys[i][1] = getPianoFreq(keys[i][1]);
      Serial.println(keys[i][1]);
    }
}

void loop() {
  // put your main code here, to run repeatedly
  curTime = millis();
  makeTone(SPEAKER_PIN, keys, KEYS_LENGTH, curTime, false);
}

/*
// Nonblocking function to make a tone for a certain duration
// Returns the index of the tone on 
int makeTone(unsigned int speakerPin, unsigned int tones[][2], unsigned long int curTime, boolean stopFlag){
  static unsigned long int curToneStartTime = 0;
  static unsigned long int curToneIndex = 0;

  // If duration has elapsed
  if(stopFlag){
    noTone(speakerPin);
  }
  else if(curTime >= (curToneStartTime + tones[curToneIndex][0])){
      //Serial.print("hit\n");
      // Roll over curToneIndex
      curToneIndex += 1;
      if(curToneIndex >= TONES_LENGTH){
        curToneIndex = 0;
      }
      // Play next tone
      tone(speakerPin, tones[curToneIndex][1]);
      // Save time
      curToneStartTime = millis();
      return curToneIndex;
  }

  return -1;
}
*/
