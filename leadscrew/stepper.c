#include "gpio.h"

#include "pico/stdlib.h"
#include "pico/time.h"

volatile uint8_t direction_set;
//  0 = no movement
//  1 = normal
//  2 = inverted

void initStepper() {
  /* code */
}

void setDir(){
  
}

void doSteps(int8_t numSteps) {
  static bool currentState;
  currentState = ! currentState;

  if (direction_set!=0){
    for (size_t i = 0; i < numSteps; i++) {
      stepPulseWrite(currentState);
      sleep_us(5);
    }
  }
}
