#include "quadrature.h"
#include "gpio.h"
#include "stepper.h"

#include "pico/time.h"
#include "pico/float.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>


volatile long long divisionCounter;
volatile long long stepCounter;

volatile uint16_t pitch_1000; //pitch multiplied by 1000

volatile uint16_t speedRPM;

volatile bool quad0State;
volatile bool quad1State;

void initialiseQuadrature(){
  divisionCounter=0;
  stepCounter=0;
  pitch_1000=1500;
  quad0State=getQuadrature0State();
  quad1State=getQuadrature1State();
}

volatile uint8_t checkDir() {
  return direction_set;
}

void pulse0irqRise() {
  quad0State=true;
  if (quad1State) {
    divisionCounter++;
  } else {
    divisionCounter--;
  }
}

void pulse1irqRise() {
  quad1State=true;
  if (quad0State) {
    divisionCounter--;
  } else {
    divisionCounter++;
  }
}

void pulse0irqFall() {
  quad0State=false;
  if (quad1State) {
    divisionCounter--;
  } else {
    divisionCounter++;
  }
}

void pulse1irqFall() {
  quad1State=false;
  if (quad0State) {
    divisionCounter++;
  } else {
    divisionCounter--;
  }
}

void doPulse(){
  long long step;
  //Do calculations for the current desired step
  step = ((NUM_STEPS * NUM_MICROSTEPS * LEADSCREW_PITCH_1000 * divisionCounter) / (NUM_DIVISIONS * pitch_1000));
  //Calculates how many steps need to be performed

  step = step - stepCounter;
  stepCounter+=step;
  if (step>0){
    direction_set=1;
  }
  else{
    direction_set=2;
  }

  setDir();
  doSteps((uint16_t) abs(step));
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
