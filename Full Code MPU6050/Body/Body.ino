#include "Reader.h"

#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

//Arbitrary Address that should be shared by Receiver & Transmitter
const uint64_t address = 250;
//float values[8] = {0};
String base ="";

Reader reader;
RF24 radio(9,10);

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();

  reader.setup();
}

void loop() {
  float* values = reader.readValues();
  for(int i = 0; i < 8; i++)
  {
    Serial.print(base + values[i] + ",");
  }
  Serial.println();
  radio.write(&values, sizeof(float[8]));
  delay(300);
}
