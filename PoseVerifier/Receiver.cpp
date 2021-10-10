#include "Receiver.h"

Receiver::Receiver(uint64_t address)
{
  radio = RF24(9, 10);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

float* Receiver::receive()
{
  radio.read(&values, sizeof(values));
  memset(serialString, 0, sizeof(serialString)); //Clean serial String to ""
  //Convert to serial string
  for(int i = 0; i < 8; i++)
  {
    //Get (3 max whole number with 2 decimal point value (6 bytes) + 
    // '-' in case of negative + end point = 8 bytes
    char valString[8];
    dtostrf(values[i], -7, 2, valString); //Convert float to char[]
    trimCh(valString);                   //Trim extra spaces
    strcat(serialString, valString);               //Concat string
    strcat(serialString, ", ");
  }
  return values;
}

char* Receiver::getSerialString()
{
  return serialString;
}

float* Receiver::getValues()
{
  return values;
}

bool Receiver::isAvailable()
{
  return radio.available();
}

void Receiver::trimCh(char *str)
{
  //Find 1st space
  char *p = strchr(str, ' ');
  if(p) *p = 0; //Set to end pointer
}
