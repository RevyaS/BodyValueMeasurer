#include "Reader.h"

Reader::Reader()
{
  Wire.begin();
}

float* Reader::readValues()
{
  //Loop through all accelerometers
  for(int i = 0; i < 4; i++)
  {
    //Switch I2C Channel
    switchChannel(channels[i]);
    //Communicate to ACC in Channel
    Wire.beginTransmission(ACC);
    Wire.write(0x32);
    Wire.endTransmission(false);
    Wire.requestFrom(ACC, 6, true); //6 Values, 3 axes (X,Y,Z) * 2 parameters of each axis(X,Y)
    for(int j = 0; j < 3;j++) //Fill in X,Y,Z to array
    {
      int index = i * 4 + j;
      values[index] = readAccValue();
    }
    Wire.endTransmission();
  }

  return values;
}

//Switch Channel of MUX
// channel - Channel number (0-7)
void Reader::switchChannel(int channel)
{
  Wire.beginTransmission(MUX);
  Wire.write(bit(channel));
  Wire.endTransmission();
}

//Reads Acc value
float Reader::readAccValue()
{
  //Accelerometer value is 10 bits but can only send 8 bits, so 1st Wire.read() is 1st 8 bits,
  //then 2nd Wire.read() is for the last 2 bits
  float value = Wire.read() | Wire.read() << 8;
  return value/256; //To limit range to +- 2g
}
