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
} DiodePortConfigurationStructure;

typedef struct {
	uint8_t rState;
	
	uint8_t gState;
	
	uint8_t bState;
	
	uint8_t rCurrentStateCounter;
	
	uint8_t rEndState;
	
	uint8_t gCurrentStateCounter;
	
	uint8_t gEndState;
	
	uint8_t bCurrentStateCounter;
	
	uint8_t bEndState;
	
	uint8_t rPulseWidthPercentage;
	
	uint8_t gPulseWidthPercentage;
	
	uint8_t bPulseWidthPercentage;
} DiodePwmStructure;

typedef struct {
	
	uint8_t rAnimationStep;
	
	uint8_t gAnimationStep;
	
	uint8_t bAnimationStep;
	
	uint8_t rTargetPulseWidthPercentage;
	
	uint8_t gTargetPulseWidthPercentage;
	
	uint8_t bTargetPulseWidthPercentage;
	
	
} DiodeAnimationStructure;


typedef struct {
	
	DiodePortConfigurationStructure diodePortConfigurationStructure;
	DiodePwmStructure diodePwmStructure;
	DiodeAnimationStructure diodeAnimationStructure;
	
	
} DiodeStructure;




#endif