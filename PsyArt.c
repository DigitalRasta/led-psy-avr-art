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
	diodeStructure->rEndState = calculateEndState(diodeStructure->rPulseWidthPercentage, diodeStructure->rState);
	diodeStructure->gEndState = calculateEndState(diodeStructure->gPulseWidthPercentage, diodeStructure->gState);
	diodeStructure->bEndState = calculateEndState(diodeStructure->bPulseWidthPercentage, diodeStructure->bState);
	
}

DiodeStructure testDiode;

int main(void)
{
	
	testDiode.portNameR = &PORTC;
	testDiode.pinNumberR = 1;
	
	testDiode.portNameG = &PORTC;
	testDiode.pinNumberG = 0;
	
	testDiode.portNameB = &PORTD;
	testDiode.pinNumberB = 7;
	
	testDiode.rState = 1;
	testDiode.gState = 0;
	testDiode.bState = 0;
	
	testDiode.rCurrentStateCounter = 0;
	testDiode.gCurrentStateCounter = 0;
	testDiode.bCurrentStateCounter = 0;
	
	testDiode.rPulseWidthPercentage = 0;
	testDiode.gPulseWidthPercentage = 0;
	testDiode.bPulseWidthPercentage = 0.3;
	
	initPortsDDR();
	initRefreshTimer();
	initEndStateForDefault(&testDiode);
    while(1)
    {
        //applyState(&testDiode);
    }
}

uint32_t counter = 0;
ISR (TIMER0_OVF_vect) // timer0 overflow interrupt
{
	updateStateCounter(&testDiode);
	checkIfStateChangeNeeded(&testDiode);
}