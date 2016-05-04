#include "DiodeFunctions.h"
void applyState(DiodeStructure* diodeStructure) {
	if(diodeStructure->rState == 1) {
		*(diodeStructure->portNameR) |= (1 << diodeStructure->pinNumberR);
	} else {
		*(diodeStructure->portNameR) &= ~(1 << diodeStructure->pinNumberR);
	}
	
	if(diodeStructure->gState == 1) {
		*(diodeStructure->portNameG) |= (1 << diodeStructure->pinNumberG);
	} else {
		*(diodeStructure->portNameG) &= ~(1 << diodeStructure->pinNumberG);
	}
	
	if(diodeStructure->bState == 1) {
		*(diodeStructure->portNameB) |= (1 << diodeStructure->pinNumberB);
	} else {
		*(diodeStructure->portNameB) &= ~(1 << diodeStructure->pinNumberB);
	}
}

void updateStateCounter(DiodeStructure* diodeStructure) {
	diodeStructure->rCurrentStateCounter++;
	diodeStructure->gCurrentStateCounter++;
	diodeStructure->bCurrentStateCounter++;
}


uint32_t calculateEndState(float pulseWidthPercentage, uint8_t state) {
	if(state == 1) {
		return 600 * pulseWidthPercentage;
	} else {
		return 600-(pulseWidthPercentage*600);
	}
}


void checkIfStateChangeNeeded(DiodeStructure* diodeStructure) {
	if(diodeStructure->rCurrentStateCounter > diodeStructure->rEndState) {
		diodeStructure->rEndState = calculateEndState(diodeStructure->rPulseWidthPercentage, diodeStructure->rState);
		diodeStructure->rState = diodeStructure->rState == 0 ? 1 : 0;
		diodeStructure->rCurrentStateCounter = 0;
		applyState(diodeStructure);
	}
	
	if(diodeStructure->gCurrentStateCounter > diodeStructure->gEndState) {
		diodeStructure->gEndState = calculateEndState(diodeStructure->gPulseWidthPercentage, diodeStructure->gState);
		diodeStructure->gState =  diodeStructure->gState == 0 ? 1 : 0;
		diodeStructure->gCurrentStateCounter = 0;
		applyState(diodeStructure);
	}
	
	if(diodeStructure->bCurrentStateCounter > diodeStructure->bEndState) {
		diodeStructure->bEndState = calculateEndState(diodeStructure->bPulseWidthPercentage, diodeStructure->bState);
		diodeStructure->bState =  diodeStructure->bState == 0 ? 1 : 0;
		diodeStructure->bCurrentStateCounter = 0;
		applyState(diodeStructure);
	}
}
