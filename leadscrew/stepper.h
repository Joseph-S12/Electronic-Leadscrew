#ifndef NUM_STEPS
#define NUM_STEPS 200
#endif

#ifndef NUM_MICROSTEPS
#define NUM_MICROSTEPS 4
#endif

extern volatile uint8_t direction_set;

extern void initStepper();
extern void setDir();
extern void doSteps(uint16_t, int);
extern void completeSteps();
