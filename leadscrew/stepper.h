#include "pico/stdlib.h"

#ifndef NUM_STEPS
#define NUM_STEPS 200
#endif

#ifndef NUM_MICROSTEPS
#define NUM_MICROSTEPS 1
#endif

extern volatile uint8_t direction_set;

extern void initStepper();
extern void setDir();
extern void doSteps(uint16_t numSteps);
extern void completeSteps();
