#include "Transmitter.h"
#include "Reader.h"

//Arbitrary Address that should be shared by Receiver & Transmitter
const uint64_t address = 250;

Transmitter transmitter(address);
Reader reader;

void setup() {
}

void loop() {
  transmitter.transmit(reader.readValues());
  delay(300);
}
