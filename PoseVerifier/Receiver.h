#ifndef RECEIVER_H
#define RECEIVER_H

#include<Arduino.h>
#include<stdlib.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

class Receiver
{
  public:
    Receiver(uint64_t address);
    float* receive();
    bool isAvailable();
    char* getSerialString();
  private:
    RF24 radio;
    // 2 values from roll & pitch * 4 accelerometers = 8 values
    float values[8];
    //String used to communicate /w Pose Generator
    //(4 values per float + ",") = 5 bytes
    // 2 floats per accelerometer (roll & pitch) = 10 bytes
    // 4 accelerometers = 40 bytes
    // 1 String ender = 41 bytes
    char serialString[41] = ""; 
};

#endif
