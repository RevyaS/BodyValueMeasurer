#include "Reader.h"
#include "SearchTree.h"

#define OUTPUT_PIN 8
//Set to 1 if connecting to processing
#define PRINT_MODE 0

Reader reader;
SearchTree searcher;

void setup() {
  if(PRINT_MODE) Serial.begin(9600);

  reader.setup();

  //Uncomment for testing  
  // reader.readChannels();
}

void loop() {
  float* values = reader.readValues();
  
  if(PRINT_MODE)
  {
    Serial.print(reader.getSerialString());
  }

  if(searcher.search(reader.readValues()))
    digitalWrite(OUTPUT_PIN, HIGH);
  else
    digitalWrite(OUTPUT_PIN, LOW);

  delay(300);
}
