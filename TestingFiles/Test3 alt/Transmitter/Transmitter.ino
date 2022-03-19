#include <Wire.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

//CALIBRATION AREA
#define xOffset 0
#define yOffset 0
#define zOffset 0
//END OF CALIBRATION

const uint64_t address = 250; //Communication Address
const int MPU6050 = 0x68; //I2C address

RF24 radio(9,10); //CE, CSN pins
float values[5]; //X,Y,Z, Roll, Pitch

void setup() {
  Wire.begin();
  //Reset Connections MPU6050
  Wire.beginTransmission(MPU6050);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(10);
    
  //For NRF24L01
  radio.begin();
  radio.openWritingPipe(address);
}

void loop() {
  Wire.beginTransmission(MPU6050); //Access ADXL345
  Wire.write(0x3B); //Access the value registers
  Wire.endTransmission(false); //End connection while retaining access
  Wire.requestFrom(MPU6050, 6, true); //2 for each axis
  values[1] = readWire() + xOffset; //1st 2 Wire.read() is for X
  values[0] = readWire() + yOffset; //Next 2 Wire.read() is for Y
  values[2] = readWire() + zOffset; //Last 2 Wire.read() is for Z

  //Compute for Roll & Pitch
  values[3] = atan(values[1] / sqrt( pow(values[0], 2) + pow(values[2], 2))) + 180/PI;
  values[4] = atan(-1 * values[2] / sqrt( pow(values[1], 2) + pow(values[0], 2))) * 180/PI;
  
  radio.write(&values, sizeof(values));
  delay(600);
}

//Reads the value from ADXL345
float readWire()
{
  //ADXL345 Accelerometer values are 10 bits but can only send 8 bits at a time
  //So 1st Wire.read() is for 1st 8 bits then 2nd Wire.read() is for last 2 bits
  float values = Wire.read() | Wire.read() << 8; //Use | to append both bits
  return values/16384; //Set range to +- 2g by dividing by 256 acc. to Data Sheet
}
