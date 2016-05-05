#include "DiodeFunctions.h"
#include <stdlib.h>
void applyState(DiodeStructure* diodeStructure) {
	if(diodeStructure->diodePwmStructure.rState == 1) {
		*(diodeStructure->diodePortConfigurationStructure.portNameR) |= (1 << diodeStructure->diodePortConfigurationStructure.pinNumberR);
	} else {
		*(diodeStructure->diodePortConfigurationStructure.portNameR) &= ~(1 << diodeStructure->diodePortConfigurationStructure.pinNumberR);
	}
	
	if(diodeStructure->diodePwmStructure.gState == 1) {
		*(diodeStructure->diodePortConfigurationStructure.portNameG) |= (1 << diodeStructure->diodePortConfigurationStructure.pinNumberG);
	} else {
		*(diodeStructure->diodePortConfigurationStructure.portNameG) &= ~(1 << diodeStructure->diodePortConfigurationStructure.pinNumberG);
	}
	
	if(diodeStructure->diodePwmStructure.bState == 1) {
		*(diodeStructure->diodePortConfigurationStructure.portNameB) |= (1 << diodeStructure->diodePortConfigurationStructure.pinNumberB);
	} else {
		*(diodeStructure->diodePortConfigurationStructure.portNameB) &= ~(1 << diodeStructure->diodePortConfigurationStructure.pinNumberB);
	}
}

void updateStateCounter(DiodeStructure* diodeStructure) {
	diodeStructure->diodePwmStructure.rCurrentStateCounter++;
	diodeStructure->diodePwmStructure.gCurrentStateCounter++;
	diodeStructure->diodePwmStructure.bCurrentStateCounter++;
}


uint8_t calculateEndState(uint8_t pulseWidthPercentage, uint8_t state) {
	if(state == 1) {
		return 254.0* ((float)pulseWidthPercentage/254);
	} else {
		return 254.0-(((float)pulseWidthPercentage/254)*254.0);
	}
}


void checkIfStateChangeNeeded(DiodeStructure* diodeStructure) {
	if(diodeStructure->diodePwmStructure.rCurrentStateCounter > diodeStructure->diodePwmStructure.rEndState) {
		diodeStructure->diodePwmStructure.rEndState = calculateEndState(diodeStructure->diodePwmStructure.rPulseWidthPercentage, diodeStructure->diodePwmStructure.rState);
		diodeStructure->diodePwmStructure.rState = diodeStructure->diodePwmStructure.rState == 0 ? 1 : 0;
		diodeStructure->diodePwmStructure.rCurrentStateCounter = 0;
		applyState(diodeStructure);
	}
	
	if(diodeStructure->diodePwmStructure.gCurrentStateCounter > diodeStructure->diodePwmStructure.gEndState) {
		diodeStructure->diodePwmStructure.gEndState = calculateEndState(diodeStructure->diodePwmStructure.gPulseWidthPercentage, diodeStructure->diodePwmStructure.gState);
		diodeStructure->diodePwmStructure.gState =  diodeStructure->diodePwmStructure.gState == 0 ? 1 : 0;
		diodeStructure->diodePwmStructure.gCurrentStateCounter = 0;
		applyState(diodeStructure);
	}
	
	if(diodeStructure->diodePwmStructure.bCurrentStateCounter > diodeStructure->diodePwmStructure.bEndState) {
		diodeStructure->diodePwmStructure.bEndState = calculateEndState(diodeStructure->diodePwmStructure.bPulseWidthPercentage, diodeStructure->diodePwmStructure.bState);
		diodeStructure->diodePwmStructure.bState =  diodeStructure->diodePwmStructure.bState == 0 ? 1 : 0;
		diodeStructure->diodePwmStructure.bCurrentStateCounter = 0;
		applyState(diodeStructure);
	}
}


void updateAnimation(DiodeStructure* diodeStructure){
	
	if(diodeStructure->diodeAnimationStructure.rTargetPulseWidthPercentage > diodeStructure->diodePwmStructure.rPulseWidthPercentage) {
		diodeStructure->diodePwmStructure.rPulseWidthPercentage += diodeStructure->diodeAnimationStructure.rAnimationStep;
	} else if (diodeStructure->diodeAnimationStructure.rTargetPulseWidthPercentage < diodeStructure->diodePwmStructure.rPulseWidthPercentage) {
		diodeStructure->diodePwmStructure.rPulseWidthPercentage -= diodeStructure->diodeAnimationStructure.rAnimationStep;
	} else {
		diodeStructure->diodeAnimationStructure.rTargetPulseWidthPercentage = rand()%254;
	}
	
	if(diodeStructure->diodeAnimationStructure.gTargetPulseWidthPercentage > diodeStructure->diodePwmStructure.gPulseWidthPercentage) {
			diodeStructure->diodePwmStructure.gPulseWidthPercentage += diodeStructure->diodeAnimationStructure.gAnimationStep;
		} else if (diodeStructure->diodeAnimationStructure.gTargetPulseWidthPercentage < diodeStructure->diodePwmStructure.gPulseWidthPercentage) {
			diodeStructure->diodePwmStructure.gPulseWidthPercentage -= diodeStructure->diodeAnimationStructure.gAnimationStep;
		} else {
		diodeStructure->diodeAnimationStructure.gTargetPulseWidthPercentage = rand()%254;
	}
	
	if(diodeStructure->diodeAnimationStructure.bTargetPulseWidthPercentage > diodeStructure->diodePwmStructure.bPulseWidthPercentage) {
		diodeStructure->diodePwmStructure.bPulseWidthPercentage += diodeStructure->diodeAnimationStructure.bAnimationStep;
		} else if (diodeStructure->diodeAnimationStructure.bTargetPulseWidthPercentage < diodeStructure->diodePwmStructure.bPulseWidthPercentage) {
		diodeStructure->diodePwmStructure.bPulseWidthPercentage -= diodeStructure->diodeAnimationStructure.bAnimationStep;
		} else {
		diodeStructure->diodeAnimationStructure.bTargetPulseWidthPercentage = rand()%254;
	}	
}

