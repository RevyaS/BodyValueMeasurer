#ifndef READER_H
#define READER_H

#include <Arduino.h>
#include <Wire.h>

class Reader
{
  public:
    Reader();
    float* readValues();
  private:
    void switchChannel(int channel);
    float readAccValue();
    //Float array
    float values[12];
    //Addresses
    const int ACC = 0x35; //ADXL35 ADDRESS - Accelerometer
    const int MUX = 0x70; //TCA9548A ADDRESS - I2X MUX
    //ORDER: Arm, Torso, Left Thigh, Right Thigh
    const int channels[4] = {7, 6, 5, 4};
};

#endif
