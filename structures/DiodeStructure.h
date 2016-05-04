#include <inttypes.h>
#ifndef DIODESTRUCTURE_H_
#define DIODESTRUCTURE_H_

typedef struct {
	volatile uint8_t *portNameR;
	uint8_t pinNumberR;
	volatile uint8_t *portNameG;
	uint8_t pinNumberG;
	volatile uint8_t *portNameB;
	uint8_t pinNumberB;
	
	uint8_t rState;
	
	uint8_t gState;
	
	uint8_t bState;
	
	uint32_t rCurrentStateCounter;
	
	uint32_t rEndState;
	
	uint32_t gCurrentStateCounter;
	
	uint32_t gEndState;
	
	uint32_t bCurrentStateCounter;
	
	uint32_t bEndState;
	
	
	float rPulseWidthPercentage;
	
	float gPulseWidthPercentage;
	
	float bPulseWidthPercentage;
	
} DiodeStructure;




#endif