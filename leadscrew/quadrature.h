#include "pico/stdlib.h"

#ifndef NUM_DIVISIONS
#define NUM_DIVISIONS 160 //Technically number of divisions of the quadrature encoder, multiplied by 4
#endif

#ifndef LEADSCREW_PITCH
#define LEADSCREW_PITCH 1.5
#endif

extern void initialiseQuadrature();
extern volatile uint8_t checkDir();

extern void pulse0irqRise();
extern void pulse1irqRise();
extern void pulse0irqFall();
extern void pulse1irqFall();

extern void doPulse(int8_t);
