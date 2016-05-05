#include "structures/DiodeStructure.h"
#include "functions/DiodeFunctions.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 8000000


void initPortsDDR() {
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
}


void initEndStateForDefault(DiodeStructure* diodeStructure) {
	diodeStructure->diodePwmStructure.rEndState = calculateEndState(diodeStructure->diodePwmStructure.rPulseWidthPercentage, diodeStructure->diodePwmStructure.rState);
	diodeStructure->diodePwmStructure.gEndState = calculateEndState(diodeStructure->diodePwmStructure.gPulseWidthPercentage, diodeStructure->diodePwmStructure.gState);
	diodeStructure->diodePwmStructure.bEndState = calculateEndState(diodeStructure->diodePwmStructure.bPulseWidthPercentage, diodeStructure->diodePwmStructure.bState);
	
}

DiodeStructure testDiode;

int main(void)
{
	srand(3);
	testDiode.diodePortConfigurationStructure.portNameR = &PORTB;
	testDiode.diodePortConfigurationStructure.pinNumberR = 4;
	
	testDiode.diodePortConfigurationStructure.portNameG = &PORTB;
	testDiode.diodePortConfigurationStructure.pinNumberG = 2;
	
	testDiode.diodePortConfigurationStructure.portNameB = &PORTB;
	testDiode.diodePortConfigurationStructure.pinNumberB = 7;
	
	testDiode.diodePwmStructure.rState = 1;
	testDiode.diodePwmStructure.gState = 0;
	testDiode.diodePwmStructure.bState = 0;
	
	testDiode.diodePwmStructure.rCurrentStateCounter = 0;
	testDiode.diodePwmStructure.gCurrentStateCounter = 0;
	testDiode.diodePwmStructure.bCurrentStateCounter = 0;
	
	testDiode.diodePwmStructure.rEndState = 800;
	testDiode.diodePwmStructure.gEndState = 800;
	testDiode.diodePwmStructure.bEndState = 800;
	
	testDiode.diodePwmStructure.rPulseWidthPercentage = 100;
	testDiode.diodePwmStructure.gPulseWidthPercentage = 100;
	testDiode.diodePwmStructure.bPulseWidthPercentage = 100;
	
	testDiode.diodeAnimationStructure.rTargetPulseWidthPercentage = 1;
	testDiode.diodeAnimationStructure.rAnimationStep = 1;
	
	testDiode.diodeAnimationStructure.gTargetPulseWidthPercentage = 1;
	testDiode.diodeAnimationStructure.gAnimationStep = 1;
	
	testDiode.diodeAnimationStructure.bTargetPulseWidthPercentage = 1;
	testDiode.diodeAnimationStructure.bAnimationStep = 1;
	
	initPortsDDR();
	initEndStateForDefault(&testDiode);
	
	uint32_t animationCounter = 0;
	uint32_t animationCounterEndStep = 300;
    while(1)
    {
        updateStateCounter(&testDiode);
        checkIfStateChangeNeeded(&testDiode);
		animationCounter++;
		if(animationCounter > animationCounterEndStep) {
			updateAnimation(&testDiode);
			animationCounter = 0;
		}
    }
}