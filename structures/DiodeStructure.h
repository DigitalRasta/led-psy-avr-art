#include <inttypes.h>
#ifndef DIODESTRUCTURE_H_
#define DIODESTRUCTURE_H_

#define TICKS_PERIOD 100.0

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
	
	uint16_t rCurrentStateCounter;
	
	uint16_t rEndState;
	
	uint16_t gCurrentStateCounter;
	
	uint16_t gEndState;
	
	uint16_t bCurrentStateCounter;
	
	uint16_t bEndState;
	
	uint16_t rPulseWidthPercentage;
	
	uint16_t gPulseWidthPercentage;
	
	uint16_t bPulseWidthPercentage;
} DiodePwmStructure;

typedef struct {
	
	uint8_t rAnimationStep;
	
	uint8_t gAnimationStep;
	
	uint8_t bAnimationStep;
	
	uint16_t rTargetPulseWidthPercentage;
	
	uint16_t gTargetPulseWidthPercentage;
	
	uint16_t bTargetPulseWidthPercentage;
	
	uint8_t rFlag;
	uint8_t gFlag;
	uint8_t bFlag;
	
	
} DiodeAnimationStructure;


typedef struct {
	
	DiodePortConfigurationStructure diodePortConfigurationStructure;
	DiodePwmStructure diodePwmStructure;
	DiodeAnimationStructure diodeAnimationStructure;
	
	
} DiodeStructure;




#endif