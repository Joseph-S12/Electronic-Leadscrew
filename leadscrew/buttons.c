#include "gpio.h"
#include "buttons.h"
#include "pico/stdlib.h"

void initButtons(){

}

int getLeadscrewMode(uint16_t spindleSpeed){
  //0 = Off
  //1 = mm pitch
  //2 = TPI
  //4 = mm feed
  //8 = inch feed
  //16 = invert direction
  //32 = is moving

  int state = 0;

  if (getMetricState() && getPitchState()) state = 1;
  else if (getImperialState() && getPitchState()) state = 2;
  else if (getMetricState() && getPowerfeedState()) state = 4;
  else if (getImperialState() && getPowerfeedState()) state = 8;
  else state = 0;

  if ((getForwardState() && getReverseState()) || (!(getForwardState()) && !(getReverseState()))) state=0;
  else if (getReverseState()) state+=16;

  if (spindleSpeed!=0) state+=32;

  printf("%i\n", state);

  return state;
}

void checkIncDec(int state){
  //Checks if operator is changing the pitch/feedrate;
  if (getIncrementState()){
    if (state & 1 == 1) setLeadscrewPitch(getPitch()+50);
    else if (state & 4 == 4) setLeadscrewPitch(getPitch()+5);
  }
  else if (getDecrementState()){
    if (state & 1 == 1) setLeadscrewPitch(getPitch()-50);
    else if (state & 4 == 4) setLeadscrewPitch(getPitch()-5);
  }
}
