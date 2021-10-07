#include <Wire.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

const uint64_t address; // Communication address
const int ADXL345 = 0x35; //I2C address

RF24 radio = RF24(9, 10);
float values[3]; //X, Y, Z 
char str[32] = "";

void setup() {
  Wire.begin();
  //Set ADXL345 to Measuring Mode
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D); //Access Power Register
  Wire.write(8); //Write for Measuring mode
  Wire.endTransmission();

  //Calibration Area
  //X Axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1E); //X offset register
  Wire.write(0); //Edit here
  Wire.endTransmission();
  delay(10);
  //Y Axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1F); //Y offset register
  Wire.write(0); //Edit here
  Wire.endTransmission();
  delay(10);
  //Z Axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x20); //Z offset register
  Wire.write(0); //Edit here
  Wire.endTransmission();
  delay(10);
  //End of Calibration Area
  
  delay(10);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(ADXL345); //Access ADXL345
  Wire.write(0x32); //Access value registers
  Wire.endTransmission(false); //End connection while retaining access
  Wire.requestFrom(ADXL345, 6, true); //2 for each axis, therefore 6
  values[0] = readWire(); //1st 2 Wire.read() is for X
  values[1] = readWire(); //Next 2 Wire.read() is for Y
  values[2] = readWire(); //Last 2 Wire.read() is for Z

  memset(str, 0, sizeof(str)); //Clean serial String to ""
  for(int i = 0; i < 3; i++)
  {
    char value[8];
    dtostrf(values[i], -7, 2, value);
    trimCh(value);
    strcat(str, value);
    strcat(str, ", ");
  }
  Serial.println(str);
  delay(600);
}

//Reads the value from ADXL345
float readWire()
{
  //ADXL345 Accelerometer values are 10 bits but can only send 8 bits at a time
  //So 1st Wire.read() is for 1st 8 bits then 2nd Wire.read() is for last 2 bits
  float values = Wire.read() | Wire.read() << 8; //Use | to append both bits
  return values;
}

float trimCh(char *str)
{
  char *p = strchr(str, ' '); //Find 1st instance of space
  if(p) *p = 0; //Terminate
}
