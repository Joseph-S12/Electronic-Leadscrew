#include "quadrature.h"
#include "gpio.h"
#include "stepper.h"

#include "pico/time.h"
#include "pico/double.h"
#include <stdlib.h>

volatile int64_t divisionCounter;
volatile int64_t stepCounter;

volatile uint8_t direction;
//  0 = no movement
//  1 = forwards
//  2 = backwards

volatile uint16_t pitch_1000; //pitch multiplied by 1000

volatile uint16_t speedRPM;

void initialiseQuadrature(){
  direction=0;
  divisionCounter=0;
  stepCounter=0;
  pitch_1000=750;
}

volatile uint8_t checkDir() {
  return direction;
}

void pulse0irqRise() {
  if (getQuadrature1State()) {
    direction = 2;
    doPulse(-1);
  } else {
    direction = 1;
    doPulse(1);
  }
}

void pulse1irqRise() {
  if (getQuadrature0State()) {
    direction = 1;
    doPulse(1);
  } else {
    doPulse(-1);
    direction = 2;
  }
}

void pulse0irqFall() {
  if (getQuadrature1State()) {
    direction = 1;
    doPulse(1);
  } else {
    direction = 2;
    doPulse(-1);
  }
}

void pulse1irqFall() {
  if (getQuadrature0State()) {
    direction = 2;
    doPulse(-1);
  } else {
    doPulse(1);
    direction = 1;
  }
}

void doPulse(int8_t count){
  float step;
  divisionCounter+=count;
  //Do calculations for the current desired step
  step = ((NUM_STEPS * NUM_MICROSTEPS * LEADSCREW_PITCH_1000 * divisionCounter) / (NUM_DIVISIONS * pitch_1000));
  //Calculates how many steps need to be performed
  if (stepCounter < 0) {
    step = step - stepCounter;
  } else {
    step = stepCounter - step;
  }

  //Rounds the number of steps to the smallest number of steps
  if (step >= 1){
    step = floor(step);
  } else if (step <= -1){
    step = ceil(step);
  } else {
    step = 0;
  }
  doSteps((int8_t) step);
  stepCounter+=step;
}

uint16_t calcRPM() {
  static int64_t oldDivisionCounter = 0;
  static int64_t oldTime = 0;
  int64_t currentTime;
  int64_t countDifference;
  int64_t timeDifference;

  currentTime = time_us_64();

  countDifference = abs((int) (divisionCounter - oldDivisionCounter));
  timeDifference = abs((int) (currentTime - oldDivisionCounter));

  speedRPM = (uint16_t) ((countDifference / NUM_DIVISIONS) / (timeDifference / 60000000));

  oldTime = currentTime;
  oldDivisionCounter = divisionCounter;

  return speedRPM;
}

uint16_t getPitch(){
  return pitch_1000;
}
