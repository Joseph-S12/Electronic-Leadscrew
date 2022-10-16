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
volatile uint64_t lastPulseTime;
volatile uint64_t currentTime;
volatile int diff;

volatile uint16_t pitch_1000; //pitch multiplied by 1000
volatile bool reverse;

volatile uint16_t speedRPM;

volatile bool quad0State;
volatile bool quad1State;

void initialiseQuadrature(){
  divisionCounter=0;
  stepCounter=0;
  lastPulseTime=time_us_64();
  pitch_1000=750;
  quad0State=getQuadrature0State();
  quad1State=getQuadrature1State();
}

void resetCounters(){
  divisionCounter = 0;
  stepCounter = 0;
}

void setLeadscrewPitch(uint16_t pitch){
  pitch_1000=pitch;
}

void setLeadscrewReverse(bool reverseThread){
  reverse=reverseThread;
}

volatile uint8_t checkDir() {
  return direction_set;
}

void pulse0irqRise() {
  currentTime = time_us_64();
  diff = (int) (currentTime - lastPulseTime);
  lastPulseTime = currentTime;
  quad0State=true;
  // if (quad1State) {
  if (getQuadrature1State()){
    divisionCounter++;
  } else {
    divisionCounter--;
  }
}

void pulse1irqRise() {
  currentTime = time_us_64();
  diff = (int) (currentTime - lastPulseTime);
  lastPulseTime = currentTime;
  quad1State=true;
  // if (quad0State) {
  if (getQuadrature0State()){
    divisionCounter--;
  } else {
    divisionCounter++;
  }
}

void pulse0irqFall() {
  currentTime = time_us_64();
  diff = (int) (currentTime - lastPulseTime);
  lastPulseTime = currentTime;
  quad0State=false;
  // if (quad1State) {
  if (getQuadrature1State()){
    divisionCounter--;
  } else {
    divisionCounter++;
  }
}

void pulse1irqFall() {
  currentTime = time_us_64();
  diff = (int) (currentTime - lastPulseTime);
  lastPulseTime = currentTime;
  quad1State=false;
  // if (quad0State) {
  if (getQuadrature0State()){
    divisionCounter++;
  } else {
    divisionCounter--;
  }
}

void doPulse(){
  long long step;
  long long currentDivisionCounter=divisionCounter;
  //Do calculations for the current desired step
  if (currentDivisionCounter!=0){
    step = (long long) ((NUM_STEPS * NUM_MICROSTEPS * (float) pitch_1000 * (float) currentDivisionCounter) / (NUM_DIVISIONS * LEADSCREW_PITCH_1000));
  }
  else{
    step = stepCounter;
  }
  //Calculates how many steps need to be performed

  step = step - stepCounter;
  stepCounter+=step;
  // printf("%ld, %ld\n", step, stepCounter);
  if ((step>0 && reverse==false) || (step<0 && reverse==true)){
    direction_set=1;
  }
  else{
    direction_set=2;
  }

  setDir();
  // if (diff<50 * NUM_MICROSTEPS) doSteps((uint16_t) abs(step), 5);
  // else if (diff<200 * NUM_MICROSTEPS) doSteps((uint16_t) abs(step), 20);
  // else if (diff<500 * NUM_MICROSTEPS) doSteps((uint16_t) abs(step), 50);
  // else if (diff<1000 * NUM_MICROSTEPS) doSteps((uint16_t) abs(step), 100);
  // else doSteps((uint16_t) abs(step), 200);
  doSteps((uint16_t) abs(step), 100);
}


uint16_t calcRPM() {
  static int64_t oldDivisionCounter;
  static int64_t oldTime;
  int64_t currentTime;
  long countDifference;
  long timeDifference;

  currentTime = time_us_64();

  countDifference = (long) abs((int) (divisionCounter - oldDivisionCounter));
  timeDifference = (long) abs((int) (currentTime - oldTime));

  speedRPM = (uint16_t) (((float) countDifference / (NUM_DIVISIONS)) / ((float) timeDifference / 60000000));

  oldTime = currentTime;
  oldDivisionCounter = divisionCounter;
  // printf("%i, %lld\n", speedRPM, (long long) (((float) countDifference / NUM_DIVISIONS) / ((float) timeDifference / 60000000)));
  return speedRPM;
}

uint16_t getPitch(){
  return pitch_1000;
}

void setPitch(uint16_t pitch){
  pitch_1000=pitch;
}
