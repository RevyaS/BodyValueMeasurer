#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

//Channels for each accelerometer
const int buses[4] {
  0,  //Torso
  0,  //Arm
  0,  //Left Thigh
  0   //Right Thigh
};

const int offsets[3] = {
  0.00,         //yOffset
  0.00,         //xOffset
  0.00          //zOffset
};

String base = "";
const int MPU6050 = 0x68,
          MUX = 0x70,
          ACCBUS = 2;
RF24 radio(9, 10); //CE, CSN

const uint64_t address = 250;
int values[8];

void setup() {
  //Setup Wireless Transceiver
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();

  //Setup I2C connection
  Wire.begin();
  //Move to channel 2 (Accelerometer location)
  switchChannel(ACCBUS);
  //Reset Connections MPU6050
  Wire.beginTransmission(MPU6050);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(10);
}

void loop()
{
  for(int i = 0; i < 4; i++)
  {
    //Switch to accelerometer
    switchChannel(buses[i]);
    //Communicate
    Wire.beginTransmission(MPU6050);
    Wire.write(0x3B);             //Access value register
    Wire.endTransmission(false);  //End connection while retaining access
    Wire.requestFrom(MPU6050, 6, true);
    int readings[3]; //Y, X, Z
     
    for(int i = 0; i < 3; i++)
    {
      readings[i] = readAcc() + offsets[i];
    }
  
    //Compute for Roll & Pitch
    values[i*2] = atan(values[0] / sqrt( pow(values[1], 2) + pow(values[2], 2))) * 180/PI;  //Roll
    values[i*2+1] =  atan(-1 * values[2] / sqrt( pow(values[0], 2) + pow(values[1], 2))) * 180/PI;  //Pitch
  }

  radio.write(&values, sizeof(values)); //Send data
  delay(100);
}

void switchChannel(int bus)
{
  if (bus > 7) return;
  //Write value in MUX in 8 bits that must have only 1 high bit
  //The position of the high bit is the channel connected by MUX
  //ex: 00100000 means channel 5
  Wire.beginTransmission(MUX);
  Wire.write(1 << bus);
  Wire.endTransmission();
}

float readAcc()
{
  //Accelerometer value is 10 bits but can only send 8 bits at a time, 
  //so 1st Wire.read() is 1st 8 bits, then 2nd Wire.read() is for the last 2 bits
  float value = Wire.read() << 8 | Wire.read();
  return value/16384; //To limit range to +- 2g
}
