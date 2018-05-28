#include <Arduino.h>
#include "PatRead.h"

bool wasPat(unsigned int patPin1, unsigned int patPin2){
	static bool prevPat = false;
	bool curPat = (!digitalRead(patPin1) || !digitalRead(patPin2));
	if(curPat && !prevPat){
		prevPat = curPat;
		return true;
	}
	prevPat = curPat;
	return false;
}
