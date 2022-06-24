#include "gpio.h"
#include "buttons.h"
#include "pico/stdlib.h"

void initButtons(){
  
}

int getLeadscrewMode(){
  //0 = Off
  //1 = mm pitch
  //2 = TPI
  //4 = mm feed
  //8 = inch feed
  //16 = invert direction

  int state = 0;

  if (getMetricState() && getPitchState()){
    state = 1;
  } else if (getImperialState() && getPitchState()){
    state = 2;
  } else if (getMetricState() && getPowerfeedState()){
    state = 4;
  } else if (getImperialState() && getPowerfeedState()){
    state = 8;
  } else{
    state = 0;
  }
  if ((getForwardState() && getReverseState()) || (!(getForwardState()) && !(getReverseState()))){
    state=0;
  } else if (getReverseState()) {
    state+=16;
  }
  return state;
}
