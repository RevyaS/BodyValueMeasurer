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
  radio.read(values, sizeof(values));
  memset(serialString, 0, sizeof(serialString)); //Clean serial String to ""
  //Convert to serial string
  for(int i = 0; i < 8; i++)
  {
    //Get (3 max whole number with 2 decimal point value (5 bytes) + "," + end char) from value
    char valString[7];
    sprintf(valString, "%.2f", values[i]);
    strcat(serialString, valString); //serialString += valString
  }
  return values;
}

char* Receiver::getSerialString()
{
  return serialString;
}

bool Receiver::isAvailable()
{
  return radio.available();
}
