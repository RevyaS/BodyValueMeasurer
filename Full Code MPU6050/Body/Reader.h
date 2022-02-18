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
    float calibrationValues[4][3] = {
      //TORSO 
      {0, 0, 0},  //X offset, Y offset, Z offset
      //Arm
      {0, 0, 0},  //X offset, Y offset, Z offset
      //Left Thigh
      {0, 0, 0},  //X offset, Y offset, Z offset
      //Right Thigh
      {0, 0, 0},  //X offset, Y offset, Z offset
    };
    void switchChannel(int channel);
    float readAccValue();
    
    //Float array (2 from Roll & pitch) * 4 Accelerometers = 7 values
    float values[8];
    float reading[3]; //X, Y, Z
    //Addresses
    const int ACC = 0x35, //ADXL35 ADDRESS - Accelerometer
              MUX = 0x70; //TCA9548A ADDRESS - I2X MUX
    //ORDER: Torso, Arm, Left Thigh, Right Thigh
    const int channels[4] = {2, 7, 3, 6};
};

#endif
