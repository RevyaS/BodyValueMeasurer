#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

const uint64_t address = 250;

RF24 radio(9,10); //CE, CSN
float values[12] = {0.025, -87.5988, -22.05889, 44.646, 798.45321, -845.123, 98.651, 0.54, -64.63215, 8.7895, 879.3, 15.78922};

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
}

void loop() {
  radio.write(values, sizeof(values));
  delay(600);
}
