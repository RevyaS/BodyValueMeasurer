#include "Transmitter.h"

Transmitter::Transmitter(uint64_t address)
{
  radio = RF24(9, 10); //CE, CSN
  this->address = address;  
  radio.begin();
  radio.openWritingPipe(address);
}

//12 floats, (3 from X,Y,Z) * 4 Accelerometers in order
void Transmitter::transmit(float data[12])
{
  radio.write(data, sizeof(data));
}
