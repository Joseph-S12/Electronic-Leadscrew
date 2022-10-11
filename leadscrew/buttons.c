#include "gpio.h"
#include "buttons.h"
#include "pico/stdlib.h"

unsigned int mmPitch, mmFeed;

void initButtons(){
  mmPitch=750;
  mmFeed=5;
}

int getLeadscrewMode(){
  //0 = Off
  //1 = mm pitch
  //2 = TPI
  //4 = mm feed
  //8 = inch feed
  //16 = invert direction
  //32 = is moving

  int state = 0;

  if (getMetricState() && getPitchState()) {
    state = 1;
    setLeadscrewPitch((uint16_t) mmPitch);
  }
  else if (getImperialState() && getPitchState()) state = 2;
  else if (getMetricState() && getPowerfeedState()) {
    state = 4;
    setLeadscrewPitch((uint16_t) mmFeed);
  }
  else if (getImperialState() && getPowerfeedState()) state = 8;
  else state = 0;



  if ((getForwardState() && getReverseState()) || (!(getForwardState()) && !(getReverseState()))) state=0;
  else if (getReverseState()) state+=16;

  return state;
}

void checkIncDec(int state){
  //Checks if operator is changing the pitch/feedrate;
  if (getIncrementState()){
    // printf("%i %i, %i %i\n", (state & 4), ((state & 4) == 4), (state & 1), (state & 1 == 1));
    if (state & 1 == 1){
      mmPitch+=50;
      setLeadscrewPitch((uint16_t) mmPitch);
    } else if ((state & 4) == 4){
      putchar('x');
      mmFeed+=1;
      setLeadscrewPitch((uint16_t) mmFeed);
    }
  }
  else if (getDecrementState()){
    if ((state & 1 == 1) && mmPitch>50){
      mmPitch-=50;
      setLeadscrewPitch((uint16_t) mmPitch);
    } else if (((state & 4) == 4) && mmFeed>1){
      mmFeed-=1;
      setLeadscrewPitch((uint16_t) mmFeed);
    }
  }
}
