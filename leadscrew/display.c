#include "display.h"
#include "gpio.h"

void initialiseDisplay() {
  bool command0[8] = {1,0,0,0,1,1,1,1};
  bool command1[8] = {0,1,0,0,0,0,0,0};
  bool command2[8] = {1,1,0,0,0,0,0,0};
  bool data[8] = {0,0,1,1,1,1,1,1};

  //initialise outputs
  displaySTBWrite(1);
  sleep_us(100);
  displayCLKWrite(1);

  //Start the board
  displaySTBWrite(0);
  for (int8_t i = 7; i >= 0; i--) {
    sleep_us(100);
    displaySIOWrite(command0[i]);
    displayCLKWrite(0);
    sleep_us(100);
    displayCLKWrite(1);
  }
  displaySTBWrite(1);
  sleep_us(100);

  //Start resetting by setting to auto increment
  displaySTBWrite(0);
  for (int8_t i = 7; i >= 0; i--) {
    sleep_us(100);
    displaySIOWrite(command1[i]);
    displayCLKWrite(0);
    sleep_us(100);
    displayCLKWrite(1);
  }
  displaySTBWrite(1);
  sleep_us(100);

  //Set start address to 0
  displaySTBWrite(0);
  for (int8_t i = 7; i >= 0; i--) {
    sleep_us(100);
    displaySIOWrite(command2[i]);
    displayCLKWrite(0);
    sleep_us(100);
    displayCLKWrite(1);
  }


  //Wipe all display digits
  for (size_t x = 0; x < 16; x++) {
    for (int8_t i = 7; i >= 0; i--) {
      sleep_us(100);
      displaySIOWrite(0);
      displayCLKWrite(0);
      sleep_us(100);
      displayCLKWrite(1);
    }
  }
  displaySTBWrite(1);
  sleep_us(100);

  //Flashes the LED`
  sleep_ms(500);
  gpio25Write(true);
  sleep_ms(500);
  gpio25Write(false);
}

void printRPM(uint32_t rpm_int) {
  bool command[8] = {1,1,0,0,0,0,0,0};
  bool number[10][8] = {{0,0,1,1,1,1,1,1},
                      {0,0,0,0,0,1,1,0},
                      {0,1,0,1,1,0,1,1},
                      {0,1,0,0,1,1,1,1},
                      {0,1,1,0,0,1,1,0},
                      {0,1,1,0,1,1,0,1},
                      {0,1,1,1,1,1,0,1},
                      {0,0,0,0,0,1,1,1},
                      {0,1,1,1,1,1,1,1},
                      {0,1,1,0,1,1,1,1}};

  //Set start address
  displaySTBWrite(0);
  for (int8_t i = 7; i >= 0; i--) {
    sleep_us(100);
    displaySIOWrite(command[i]);
    displayCLKWrite(0);
    sleep_us(100);
    displayCLKWrite(1);
  }


  //Wipe all display digits
  for (size_t x = 0; x < 8; x++) {
    for (int8_t i = 7; i >= 0; i--) {
      sleep_us(100);
      displaySIOWrite(number[x][i]);
      displayCLKWrite(0);
      sleep_us(100);
      displayCLKWrite(1);
    }
    for (int8_t i = 7; i >= 0; i--) {
      sleep_us(100);
      displaySIOWrite(0);
      displayCLKWrite(0);
      sleep_us(100);
      displayCLKWrite(1);
    }
  }
  displaySTBWrite(1);
  sleep_us(100);
}

void printPitch(uint32_t pitch_int) {

}
