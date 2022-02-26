#include "Reader.h"

Reader::Reader()
{
}

void Reader::setup()
{
  Wire.begin();
  for(int i = 0; i < 4; i++)
  {
    //Move to channel 2 (Accelerometer location)
    switchChannel(channels[i]);
    //Reset Connections MPU6050
    Wire.beginTransmission(ACC);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission(true);
    delay(10);
  }
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
      reading[j] = readAccValue() + calibrationValues[i][j];
    }
    //Roll & Pitch formula is derived by multiplying the scalar of Accelerometer values to the
    //3D Rotation Matrix then solve for the formula of the 2 angles, roll & pitch
    float roll = atan(reading[1]/ sqrt(pow(reading[0], 2) + pow(reading[2], 2))) * 180/PI;
    values[i * 2] = roll;
    float pitch = atan(-1 * reading[0]/ sqrt(pow(reading[1], 2) + pow(reading[2], 2))) * 180/PI;
    values[i * 2 + 1] = pitch;
    Wire.endTransmission();
  }

  return values;
}

//Switch Channel of MUX
// channel - Channel number (0-7)
void Reader::switchChannel(int channel)
{
  Wire.beginTransmission(MUX);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

//Reads Accelerometer value
float Reader::readAccValue()
{
  //Accelerometer value is 10 bits but can only send 8 bits at a time, 
  //so 1st Wire.read() is 1st 8 bits, then 2nd Wire.read() is for the last 2 bits
  float value = Wire.read() | Wire.read() << 8;
  return value/256; //To limit range to +- 2g
}
