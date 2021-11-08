#include <Wire.h>

const int MPU6050 = 0x68;
const String base = "";

void setup() {
  Serial.begin(9600);

  Wire.begin();
  //Reset Connections MPU6050
  Wire.beginTransmission(MPU6050);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void loop() {
  //Request Data
  Wire.beginTransmission(MPU6050);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050, 6, true);

  float x = readAcc();
  float y = readAcc();
  float z = readAcc();

  Serial.println(base + (String)x + "," + y + "," + z);

}

float readAcc()
{
  float value = Wire.read() | Wire.read() << 8;
  return value/16384; //+-2g
}
