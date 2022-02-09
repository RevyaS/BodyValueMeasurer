#ifndef READER_H
#define READER_H

#include <Arduino.h>
#include <Wire.h>

class Reader
{
  public:
    Reader();
    void setup();
    float* readValues();
    void readChannels();
    char* getSerialString();
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

    float multiplicationValues[4][3] = {
       //TORSO 
      {0, 0, 0},  //X offset, Y offset, Z offset
      //Arm
      {0, 0, 0},  //X offset, Y offset, Z offset
      //Left Thigh
      {0, 0, 0},  //X offset, Y offset, Z offset
      //Right Thigh
      {0, 0, 0},  //X offset, Y offset, Z offset
    }
    
    void switchChannel(int channel);
    float readAccValue();
    
    //Float array (2 from Roll & pitch) * 4 Accelerometers = 7 values
    float values[8];
    float reading[3]; //X, Y, Z
    //Addresses
    const int ACC = 0x68, //ADXL35 ADDRESS - Accelerometer
              MUX = 0x70; //TCA9548A ADDRESS - I2X MUX
              
    //ORDER: Torso, Arm, Left Thigh, Right Thigh
    const int channels[4] = {2, 7, 3, 6};
    
    //String used to communicate /w Pose Generator
    //(5 values per float /w "." & "-" + ",") = 8 bytes
    // 2 floats per accelerometer (roll & pitch) = 16 bytes
    // 4 accelerometers = 64 bytes + "end point" = 65 bytes
    // +5 extra values just in case = 70 bytes
    char serialString[70] = "";

    //Sub Functions
    void trimCh(char *str); //Trims empty spaces on the right
    void appendFloat(float value, char* string);  //Appends float to char[]
};

#endif
