#include "pico/stdlib.h"


#ifndef QUADRATURE_PIN0
#define QUADRATURE_PIN0 0   //Input, Pin 0
#define QUADRATURE_PIN1 1   //Input, Pin 1

#define METRIC_PIN 2        //Input, Pin 3
#define IMPERIAL_PIN 3      //Input, Pin 4
#define PITCH_PIN 4         //Input, Pin 5
#define POWERFEED_PIN 5     //Input, Pin 6

#define INCREASE_PIN 6      //Input, Pin 8
#define DECREASE_PIN 7      //Input, Pin 9

#define FORWARD_PIN 8       //Input, Pin 10
#define REVERSE_PIN 9       //Input, Pin 11

#define STEP_DIR_PIN 11     //Input, Pin 13
#define STEP_PUL_PIN 12     //Input, Pin 14

#define DISPLAY_CLK_PIN 18   //Output, Pin 24
#define DISPLAY_SIO_PIN 19   //Output, Pin 25
#define DISPLAY_STB_PIN 20   //Output, Pin 26
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
