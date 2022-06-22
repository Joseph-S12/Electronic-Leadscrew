#include "main.h"
#include "gpio.h"
#include "gpio.c"
#include "quadrature.h"
#include "quadrature.c"
#include "stepper.h"
#include "stepper.c"
#include "display.h"
#include "display.c"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/time.h"
#include <stdio.h>

//This is the initialisation code for core 0. Everything on this core after initialisation is interrupt driven and deals with the quadrature encoder and driving the stepper.
//It is interrupted by the quadrature encoder pulses.
void main() {
  multicore_launch_core1(&main_core1);

  initGPIO0();
  initStepper();
  stdio_init_all();
  initialiseQuadrature();


  while (true){
    sleep_ms(1000);
  }
}

//This is the initialisation and run-time code of core 1. It deals with the 'user interface' (7 segment display and buttons).
//It is not interrupt driven, with the exception of the forwards/reverse switch
void main_core1() {
  initGPIO1();
  initialiseDisplay();

  while (true){
    updateRPM(calcRPM());
    updatePitch(getPitch());
    printDisplay();
  }
}
