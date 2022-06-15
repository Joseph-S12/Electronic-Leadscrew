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

#define FORWARD_PIN 9
#define REVERSE_PIN 10

#define STEP_DIR_PIN 11
#define STEP_PUL_PIN 12

#define DISPLAY_CLK_PIN 18
#define DISPLAY_SIO_PIN 19
#define DISPLAY_STB_PIN 20
#endif



extern void initGPIO0();
extern void initGPIO1();
extern void gpioCallback0(uint gpio, uint32_t events);
extern void gpioCallback1(uint gpio, uint32_t events);
extern void gpio25Write(bool state);
extern void stepPulseWrite(bool state);
extern void stepDirWrite(bool state);
extern void displaySIOWrite(bool state);
extern void displayCLKWrite(bool state);
extern void displaySTBWrite(bool state);
