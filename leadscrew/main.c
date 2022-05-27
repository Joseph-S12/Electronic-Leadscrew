#include "gpio.h"
#include "gpio.c"
#include "quadrature.h"
#include "quadrature.c"

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

void main() {
  initGPIO();
  stdio_init_all();
  initialiseQuadrature();

  while (true) {
    gpio25Write(1);
    sleep_ms(1000);
    gpio25Write(0);
    sleep_ms(2000);
  }
}
