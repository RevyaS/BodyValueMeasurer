#include "Reader.h"

#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

//Arbitrary Address that should be shared by Receiver & Transmitter
const uint64_t address = 250;

Reader reader;
RF24 radio(9,10);

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  float* values = reader.readValues();
  radio.write(&values, sizeof(values));
  delay(300);
}
