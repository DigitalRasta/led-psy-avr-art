#include "../structures/DiodeStructure.h"

#ifndef STATEFUNCTIONS_H_
#define STATEFUNCTIONS_H_


void applyState(DiodeStructure* diodeStructure);

void updateStateCounter(DiodeStructure* diodeStructure);

uint32_t calculateEndState(float rPulseWidthPercentage, uint8_t bState);

void checkIfStateChangeNeeded(DiodeStructure* diodeStructure);
#endif