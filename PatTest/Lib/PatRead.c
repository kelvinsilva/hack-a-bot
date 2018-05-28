#include "PatRead.h"

boolean wasPat(unsigned int patPin1, unsigned int patPin2){
	static boolean prevPat = false;
	boolean curPat = (!digitalRead(patPin1) || !digitalRead(patPin2));
	if(curPat && !prevPat){
		prevPat = curPat;
		return true;
	}
	prevPat = curPat;
	return false;
}