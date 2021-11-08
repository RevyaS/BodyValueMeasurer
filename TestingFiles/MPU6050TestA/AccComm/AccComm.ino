#include <Wire.h>

const int MPU6050 = 0x68,
          MUX = 0x70,
          bus = 6;

const String base = "";

void setup() {
  Serial.begin(9600);

  Wire.begin();
  
  switchChannel(bus);
  //Reset Connections MPU6050
  Wire.beginTransmission(MPU6050);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void loop() {
  //Request Data
  switchChannel(bus);
  Wire.beginTransmission(MPU6050);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050, 6, true);

  float x = readAcc();
  float y = readAcc();
  float z = readAcc();

  Serial.println(base + (String)x + "," + y + "," + z);

}

void switchChannel(int channel)
{
  Wire.beginTransmission(MUX);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

float readAcc()
{
  float value = Wire.read() | Wire.read() << 8;
  return value/16384; //+-2g
}
