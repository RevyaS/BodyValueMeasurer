#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

const uint64_t address;

RF24 radio = RF24(9, 10);
float values[5]; 
char str[64] = "";

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
     for(int i = 0; i < 5; i++)
     {
      //Get (3 max whole number with 2 decimal point value (5 bytes) /w decimal point (6 bytes) + "," + end char) from value
      char valString[8];
      sprintf(valString, "%.2f,", values[i]);
      strcat(str, valString);
     }
     Serial.println(str);
  }
  delay(200);
}
