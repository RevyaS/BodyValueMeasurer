#include "Receiver.h"

//Address : 250
Receiver receiver(250);

void setup() {
  Serial.begin(9600);
  //Serial.println(sizeof(receiver));
}

void loop() {
  if(receiver.isAvailable())
  {
    receiver.receive();
    Serial.println(receiver.getSerialString());
  }

  delay(300);
}
