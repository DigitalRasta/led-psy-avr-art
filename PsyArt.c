#include "structures/DiodeStructure.h"
#include "functions/DiodeFunctions.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000


void initPortsDDR() {
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
}

void initRefreshTimer() {
	TIMSK |= (1 << TOIE0);
	sei();
	TCCR0 |= (1 << CS00);
	TCNT0 = 0;	
}

void initEndStateForDefault(DiodeStructure* diodeStructure) {
	diodeStructure->diodePwmStructure.rEndState = calculateEndState(diodeStructure->diodePwmStructure.rPulseWidthPercentage, diodeStructure->diodePwmStructure.rState);
	diodeStructure->diodePwmStructure.gEndState = calculateEndState(diodeStructure->diodePwmStructure.gPulseWidthPercentage, diodeStructure->diodePwmStructure.gState);
	diodeStructure->diodePwmStructure.bEndState = calculateEndState(diodeStructure->diodePwmStructure.bPulseWidthPercentage, diodeStructure->diodePwmStructure.bState);
	
}

DiodeStructure testDiode;

int main(void)
{
	
	testDiode.diodePortConfigurationStructure.portNameR = &PORTC;
	testDiode.diodePortConfigurationStructure.pinNumberR = 1;
	
	testDiode.diodePortConfigurationStructure.portNameG = &PORTC;
	testDiode.diodePortConfigurationStructure.pinNumberG = 0;
	
	testDiode.diodePortConfigurationStructure.portNameB = &PORTD;
	testDiode.diodePortConfigurationStructure.pinNumberB = 7;
	
	testDiode.diodePwmStructure.rState = 1;
	testDiode.diodePwmStructure.gState = 0;
	testDiode.diodePwmStructure.bState = 0;
	
	testDiode.diodePwmStructure.rCurrentStateCounter = 0;
	testDiode.diodePwmStructure.gCurrentStateCounter = 0;
	testDiode.diodePwmStructure.bCurrentStateCounter = 0;
	
	testDiode.diodePwmStructure.rPulseWidthPercentage = 0.9;
	testDiode.diodePwmStructure.gPulseWidthPercentage = 0.9;
	testDiode.diodePwmStructure.bPulseWidthPercentage = 0.1;
	
	initPortsDDR();
	initRefreshTimer();
	initEndStateForDefault(&testDiode);
    while(1)
    {
        //applyState(&testDiode);
    }
}

uint32_t counter = 0;
ISR (TIMER0_OVF_vect)
{
	updateStateCounter(&testDiode);
	checkIfStateChangeNeeded(&testDiode);
}