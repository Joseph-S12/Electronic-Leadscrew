#ifndef NUM_DIVISIONS
#define NUM_DIVISIONS 60 //Technically number of divisions of the quadrature encoder, multiplied by 4
#endif

#ifndef LEADSCREW_PITCH_1000
#define LEADSCREW_PITCH_1000 1500
#endif

extern void initialiseQuadrature();
extern volatile uint8_t checkDir();

extern void pulse0irqRise();
extern void pulse1irqRise();
extern void pulse0irqFall();
extern void pulse1irqFall();

extern void doPulse(int8_t);

extern uint16_t calcRPM();
extern uint16_t getPitch();
