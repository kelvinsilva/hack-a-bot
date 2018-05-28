// ToneGeneration.h
// For the UCSC IEEE Hack-A-Bot 2018
// Created by Benjamin Swanson


// Defines


//Functions

// makeTone()
// Controls a speaker with an array of 2-D vectors that describe the
// duration and the frequency of a sequence of tones. tone[][0] is the durration
// in ms, tone[][1] is the frequency. This function should be run continuously.
// To stop the tone, set stopFlag to true.
// Returns the index of the tone it is playing when it changes, or -1 if the
// tone does not change.
int makeTone(unsigned int speakerPin, unsigned int tones[][2], unsigned int tonesLength, unsigned long int curTime, boolean stopFlag);

// getPianoFreq()
// Returns the piano tone of a key as a frequency.
int getPianoFreq(int key);