#include "gpio.h"

#include "pico/stdlib.h"
#include "pico/time.h"

volatile uint8_t direction_set;

volatile long long stepsToDo = 0;
//  0 = no movement
//  1 = normal
//  2 = inverted

void initStepper() {
  direction_set=1;
}

void setDir(){
  if (direction_set==2) {
    stepDirWrite(1);
  } else {
    stepDirWrite(0);
  }
}

void doSteps(uint16_t numSteps) {
  stepsToDo+=(long long) numSteps;
}

void completeSteps(){
  if (direction_set!=0 && stepsToDo>0) {
    stepPulseWrite(1);
    sleep_us(20);
    stepPulseWrite(0);
    sleep_us(20);
    stepsToDo--;
  }
}
