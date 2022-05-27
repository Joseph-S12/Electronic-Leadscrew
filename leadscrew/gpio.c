#include "quadrature.h"
#include "gpio.h"

#include "pico/stdlib.h"


void initGPIO(){
  gpio_init(QUADRATURE_PIN0);
  gpio_set_dir(QUADRATURE_PIN0, GPIO_IN);
  gpio_pull_up(QUADRATURE_PIN0);
  gpio_set_irq_enabled_with_callback(QUADRATURE_PIN0, 0b1100, true, &gpioCallback);

  gpio_init(QUADRATURE_PIN1);
  gpio_set_dir(QUADRATURE_PIN1, GPIO_IN);
  gpio_pull_up(QUADRATURE_PIN1);
  gpio_set_irq_enabled_with_callback(QUADRATURE_PIN1, 0b1100, true, &gpioCallback);

  gpio_init(MM_PITCH_PIN);
  gpio_set_dir(MM_PITCH_PIN, GPIO_IN);
  gpio_pull_up(MM_PITCH_PIN);

  gpio_init(TPI_PITCH_PIN);
  gpio_set_dir(TPI_PITCH_PIN, GPIO_IN);
  gpio_pull_up(TPI_PITCH_PIN);

  gpio_init(MM_MIN_POWERFEED_PIN);
  gpio_set_dir(MM_MIN_POWERFEED_PIN, GPIO_IN);
  gpio_pull_up(MM_MIN_POWERFEED_PIN);

  gpio_init(INCH_MIN_POWERFEED_PIN);
  gpio_set_dir(INCH_MIN_POWERFEED_PIN, GPIO_IN);
  gpio_pull_up(INCH_MIN_POWERFEED_PIN);

  gpio_init(INCREASE_PIN);
  gpio_set_dir(INCREASE_PIN, GPIO_IN);
  gpio_pull_up(INCREASE_PIN);

  gpio_init(DECREASE_PIN);
  gpio_set_dir(DECREASE_PIN, GPIO_IN);
  gpio_pull_up(DECREASE_PIN);

  gpio_init(25);
  gpio_set_dir(25, GPIO_OUT);
}

void gpioCallback(uint gpio, uint32_t events) {
  switch (gpio) {
    case 0:
    break;
    case 1:
    break;
    default:
    break;
  }
}

bool getQuadrature0State(){
  return gpio_get(QUADRATURE_PIN0);
}

bool getQuadrature1State(){
  return gpio_get(QUADRATURE_PIN1);
}

void gpio25Write(bool state){
  gpio_put(25,state);
}
