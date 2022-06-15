#include "quadrature.h"
#include "gpio.h"
#include "stepper.h"

#include "pico/stdlib.h"


void initGPIO0(){
  gpio_init(QUADRATURE_PIN0);
  gpio_set_dir(QUADRATURE_PIN0, GPIO_IN);
  gpio_pull_up(QUADRATURE_PIN0);
  gpio_set_irq_enabled_with_callback(QUADRATURE_PIN0, 0b1100, true, &gpioCallback0);

  gpio_init(QUADRATURE_PIN1);
  gpio_set_dir(QUADRATURE_PIN1, GPIO_IN);
  gpio_pull_up(QUADRATURE_PIN1);
  gpio_set_irq_enabled_with_callback(QUADRATURE_PIN1, 0b1100, true, &gpioCallback0);

  gpio_init(STEP_PUL_PIN);
  gpio_set_dir(STEP_PUL_PIN, GPIO_OUT);

  gpio_init(STEP_DIR_PIN);
  gpio_set_dir(STEP_DIR_PIN, GPIO_OUT);

  gpio_init(25);
  gpio_set_dir(25, GPIO_OUT);
}

void initGPIO1(){
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

  gpio_init(FORWARD_PIN);
  gpio_set_dir(FORWARD_PIN, GPIO_IN);
  gpio_pull_up(FORWARD_PIN);
  gpio_set_irq_enabled_with_callback(FORWARD_PIN, 0b1100, true, &gpioCallback1);

  gpio_init(REVERSE_PIN);
  gpio_set_dir(REVERSE_PIN, GPIO_IN);
  gpio_pull_up(REVERSE_PIN);
  gpio_set_irq_enabled_with_callback(REVERSE_PIN, 0b1100, true, &gpioCallback1);

  gpio_init(DISPLAY_CLK_PIN);
  gpio_set_dir(DISPLAY_CLK_PIN, GPIO_OUT);
  gpio_pull_up(DISPLAY_CLK_PIN);

  gpio_init(DISPLAY_SIO_PIN);
  gpio_set_dir(DISPLAY_SIO_PIN, GPIO_OUT);
  gpio_pull_up(DISPLAY_SIO_PIN);

}

void gpioCallback0(uint gpio, uint32_t events) { //Events is the state of the interrupt mask
  switch (gpio) {
    case QUADRATURE_PIN0:
      if (events == 0b1000){
        pulse0irqRise();
      } else if (events == 0b0100){
        pulse0irqFall();
      }//Else do nothing
      break;
    case QUADRATURE_PIN1:
      if (events == 0b1000){
        pulse1irqRise();
      } else if (events == 0b0100){
        pulse1irqFall();
      }//Else do nothing
      break;
    default:
      break;
  }
}

void gpioCallback1(uint gpio, uint32_t events) { //Events is the state of the interrupt mask
  switch (gpio) {
    case FORWARD_PIN:
      if (events == 0b1000){
        direction_set = 1;
      } else if (events == 0b0100){
        direction_set = 0;
      }//Else do nothing
      break;
    case REVERSE_PIN:
      if (events == 0b1000){
        direction_set = 2;
      } else if (events == 0b0100){
        direction_set = 0;
      }//Else do nothing
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

void stepPulseWrite(bool state) {
  gpio_put(STEP_PUL_PIN,state);
}

void stepDirWrite(bool state) {
  gpio_put(STEP_DIR_PIN,state);
}

void gpio25Write(bool state){
  gpio_put(25,state);
}

void displaySIOWrite(bool state) {
  gpio_put(DISPLAY_SIO_PIN,state);
}

void displayCLKWrite(bool state) {
  gpio_put(DISPLAY_CLK_PIN,state);
}

void displaySTBWrite(bool state) {
  gpio_put(DISPLAY_STB_PIN,state);
}
