#include "gpio.h"

#include "pico/stdlib.h"
#include "pico/time.h"

volatile uint8_t direction_set;
volatile uint64_t lastPulseTime;
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

int calcPulseSpeed(uint16_t numSteps){
  uint64_t currentTime = time_us_64();
  uint64_t diff = currentTime - lastPulseTime;
  lastPulseTime = currentTime;
  if (diff > 1000*numSteps){
    return 1000;
  }
  else{
    return (int) (diff / numSteps);
  }
}

void doSteps(uint16_t numSteps) {
  int pulseLen = calcPulseSpeed();
  for (size_t i = 0; i < numSteps; i++) {
    stepPulseWrite(1);
    sleep_us(pulseLen);
    stepPulseWrite(0);
    sleep_us(pulseLen);
  }
}
