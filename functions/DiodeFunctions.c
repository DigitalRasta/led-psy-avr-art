#include "DiodeFunctions.h"
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


uint32_t calculateEndState(float pulseWidthPercentage, uint8_t state) {
	if(state == 1) {
		return 600 * pulseWidthPercentage;
	} else {
		return 600-(pulseWidthPercentage*600);
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
