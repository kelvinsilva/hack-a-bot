#include <Arduino.h>
# include "ToneGeneration.h"

int makeTone(unsigned int speakerPin, unsigned int tones[][2], unsigned int tonesLength, unsigned long int curTime, bool stopFlag){
  static unsigned long int curToneStartTime = 0;
  static unsigned long int curToneIndex = 0;

  // If duration has elapsed
  if(stopFlag){
    noTone(speakerPin);
    curToneIndex = 0;
    curToneStartTime = 0;
    return -1;
  }
  else if(curTime >= (curToneStartTime + tones[curToneIndex][0])){
      //Serial.print("hit\n");
      // Roll over curToneIndex
      curToneIndex += 1;
      if(curToneIndex >= tonesLength){
        curToneIndex = 0;
      }
      // Play next tone
      if(tones[curToneIndex][1] != 0){
        tone(speakerPin, tones[curToneIndex][1]);
      }else{
        noTone(speakerPin);
      }
      // Save time
      curToneStartTime = millis();
      return curToneIndex;
  }

  return -1;
}

unsigned int getPianoFreq(unsigned int key){
	double freq;

  if(key == 0){
    return 0;
  }

	freq = pow(2, ((double)key-49)/12);
	freq *= 440;
	return (unsigned int) freq;
}
