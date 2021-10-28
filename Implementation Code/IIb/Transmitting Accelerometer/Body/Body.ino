#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

const int offsets[3] = {
  0.00,         //xOffset
  0.00,         //yOffset
  0.00          //zOffset
};

const int ADXL345 = 0x53,
          MUX = 0x70,
          ACCBUS = 2;
RF24 radio(9, 10); //CE, CSN
//1 acc value = 3 digits + 2 decimals + '.' + '-' = 7 bytes
//3 acc values = 7 * 3 = 21 bytes
//3 ',' between acc value = 3 bytes (3 + 21) = 24 total bytes
//Add end value = 25 total bytes, + 3 bytes for good luck = 28 bytes
char data[28] = "";

const uint64_t address = 250; 

void setup() {
  //Setup Wireless Transceiver
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();

  //Setup I2C connection
  Wire.begin();
  //Move to channel 2 (Accelerometer location)
  switchChannel(ACCBUS);
  //Set ADXL345 to Measuring Mode
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);   //Access Power Register
  Wire.write(8);      //Write for Measuring mode
  Wire.endTransmission();
  delay(10);
}

void loop()
{
  //Clear data string
  memset(data,0, sizeof(data));
  //Switch to accelerometer
  switchChannel(ACCBUS);
  //Communicate
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);             //Access value register
  Wire.endTransmission(false);  //End connection while retaining access
  Wire.requestFrom(ADXL345, 6, true);
  int values[3];  //X, Y, Z
  for(int i = 0; i < 3; i++)
  {
    values[i] = readAcc() + offsets[i];
  }

  for(int i = 0; i < 3; i++)
  {
    char val[8] = "";               //We need 7 values for the acc value + end pointer
    dtostrf(values[i], -7, 2, val); //Convert float to char[]. 
                                    //(float value, total bytes consumed, max decimal points, char[] where to save)
    trimCh(val);                    //Remove whitespaces
    strcat(data, val);              //data += val
    strcat(data, ", ");             //data += ", "
  }
  
  radio.write(&data, sizeof(data)); //Send data
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

void trimCh(char *str)
{
  //Find 1st space
  char *p = strchr(str, ' ');
  if(p) *p = 0; //Set to end pointer
}

float readAcc()
{
  //Accelerometer value is 10 bits but can only send 8 bits at a time, 
  //so 1st Wire.read() is 1st 8 bits, then 2nd Wire.read() is for the last 2 bits
  float value = Wire.read() | Wire.read() << 8;
  return value/256; //To limit range to +- 2g
}
