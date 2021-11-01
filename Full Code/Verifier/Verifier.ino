#include "Receiver.h"
#include "SearchTree.h"

#define OUTPUT_PIN 8  //Feel free to edit this

//Address : 250
Receiver receiver(250);
SearchTree searcher;

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  if(receiver.isAvailable())
  {
    receiver.receive();
    Serial.println(receiver.getSerialString());
    if(searcher.search(receiver.getValues()))
      digitalWrite(OUTPUT_PIN, HIGH);
    else
      digitalWrite(OUTPUT_PIN, LOW);
  }

  delay(300);
}
