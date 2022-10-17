#include "gpio.h"

#include "pico/stdlib.h"
#include "pico/time.h"

volatile uint8_t direction_set;
//  0 = no movement
//  1 = normal
//  2 = inverted

void initStepper() {
  direction_set=1;
  lastPulseTime=time_us_64();
}

void setDir(){
  if (direction_set==2) {
    stepDirWrite(1);
  } else {
    stepDirWrite(0);
  }
}

void doSteps(uint16_t numSteps, int pulseLen) {
  for (size_t i = 0; i < numSteps; i++) {
    stepPulseWrite(1);
    sleep_us(5);
    stepPulseWrite(0);
    sleep_us(pulseLen);
  }
}
