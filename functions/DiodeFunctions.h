#include "../structures/DiodeStructure.h"

#ifndef STATEFUNCTIONS_H_
#define STATEFUNCTIONS_H_


void applyState(DiodeStructure* diodeStructure);

void updateStateCounter(DiodeStructure* diodeStructure);

void updateAnimation(DiodeStructure* diodeStructure);

uint8_t calculateEndState(uint8_t rPulseWidthPercentage, uint8_t bState);

void checkIfStateChangeNeeded(DiodeStructure* diodeStructure);
#endif