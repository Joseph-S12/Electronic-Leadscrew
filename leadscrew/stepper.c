#include "gpio.h"

#include "pico/stdlib.h"
#include "pico/time.h"

void doSteps(int8_t numSteps) {
  gpio25Write(1);
  sleep_ms(100);
  gpio25Write(0);
  sleep_ms(200);
}
