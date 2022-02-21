#include <Wire.h>

//CALIBRATION AREA
#define xOffset 0
#define yOffset 0
#define zOffset 0

const uint64_t address; // Communication address
const int ADXL345 = 0x53; //I2C address
const int ADXL345ALT = 0x1D;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //Test 1st Address
  Wire.beginTransmission(ADXL345);
  if(!Wire.endTransmission())
  {
    Serial.print("Address is 0x53");
    return;
  }
  delay(10);
  //Test 2nd Address
  Wire.beginTransmission(ADXL345ALT);
  if(!Wire.endTransmission())
  {
    Serial.print("Address is 0x1D");
    return;
  }
  delay(10);
  Serial.print("No ADXL345 is connected");
}

void loop() {
}
