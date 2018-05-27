# include "ToneGeneration.h"

int makeTone(unsigned int speakerPin, unsigned int tones[][2], unsigned int tonesLength, unsigned long int curTime, boolean stopFlag){
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
      if(curToneIndex >= tonesLength){
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

unsigned int getPianoFreq(unsigned int key){
	double freq;
	freq = pow(2, (key-49)/12);
	freq *= 440;
	return (unsigned int) freq;
}