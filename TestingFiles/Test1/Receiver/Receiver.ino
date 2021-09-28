#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

const uint64_t address;

RF24 radio = RF24(9, 10);
float values[12]; 
char str[72] = "";

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if(radio.available())
  {
     memset(str, 0, sizeof(str));
     radio.read(values, sizeof(values));
     for(int i = 0; i < 12; i++)
     {
      //Get (3 max whole number with 2 decimal point value (5 bytes) + "," + end char) from value
      char valString[7];
      sprintf(valString, "%.2f", values[i]);
      strcat(str, valString);
     }
     Serial.println(str);
  }
  delay(200);
}
