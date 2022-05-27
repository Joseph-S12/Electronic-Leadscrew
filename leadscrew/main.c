#include "gpio.h"
#include "gpio.c"
#include "quadrature.h"
#include "quadrature.c"
#include "stepper.h"
#include "stepper.c"

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

void main() {
  initGPIO();
  stdio_init_all();
  initialiseQuadrature();

  while (true);
}
