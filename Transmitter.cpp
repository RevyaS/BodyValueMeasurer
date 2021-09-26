#include "Transmitter.h"

Transmitter::Transmitter(uint64_t address)
{
  RF24 radio(9, 10);
  this->address = address;  
  radio.begin();
  radio.openWritingPipe(address);
}

//12 floats, (3 from X,Y,Z) * 4 Accelerometers in order
void Transmitter::transmit(float data[12])
{
  radio.write(data, sizeof(data));
}
