#include "pico/stdlib.h"


#ifndef QUADRATURE_PIN0
#define QUADRATURE_PIN0 0
#define QUADRATURE_PIN1 1

#define MM_PITCH_PIN 2
#define TPI_PITCH_PIN 3
#define MM_MIN_POWERFEED_PIN 4
#define INCH_MIN_POWERFEED_PIN 5

#define INCREASE_PIN 6
#define DECREASE_PIN 7
#endif



extern void initGPIO();
extern void gpioCallback(uint gpio, uint32_t events);
extern void gpio25Write(bool state);
