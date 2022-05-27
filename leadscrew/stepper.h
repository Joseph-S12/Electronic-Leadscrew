#include "pico/stdlib.h"

#ifndef NUM_STEPS
#define NUM_STEPS 200
#endif

#ifndef NUM_MICROSTEPS
#define NUM_MICROSTEPS 8
#endif

extern void doSteps(int8_t numSteps);
