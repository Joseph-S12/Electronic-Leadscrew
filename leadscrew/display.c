#include "display.h"
#include "gpio.h"

void printRPM(uint32_t rpm_int) {
  bool command0[] = {0,1,0,0,0,0,0,0};
  bool command1[] = {1,1,0,0,0,0,0,0};
  bool data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  displayCLKWrite(1);
  displaySTBWrite(0);
  for (size_t i = 8; i > 0; i--) {
    sleep_us(10);
    displaySIOWrite(command0[i]);
    displayCLKWrite(0);
    sleep_us(10);
    displayCLKWrite(1);
  }
  sleep_us(10);
  displaySTBWrite(1);
  sleep_us(10);
  displaySTBWrite(0);
  for (size_t i = 8; i > 0; i--) {
    sleep_us(10);
    displaySIOWrite(command1[i]);
    displayCLKWrite(0);
    sleep_us(10);
    displayCLKWrite(1);
  }
  for (size_t i = 16; i > 0; i--) {
    sleep_us(10);
    displaySIOWrite(data[i]);
    displayCLKWrite(0);
    sleep_us(10);
    displayCLKWrite(1);
  }
  displaySTBWrite(1);

  sleep_ms(500);
  gpio25Write(true);
  sleep_ms(500);
  gpio25Write(false);
}

void printPitch(uint32_t pitch_int) {

}
