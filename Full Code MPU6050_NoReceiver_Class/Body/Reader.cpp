#include "Reader.h"

Reader::Reader()
{
}

void Reader::setup()
{
  Wire.begin();
  //Configure each accelerometer
  for(int i = 0; i > 4; i++)
  {
    //Set acc to reading mode
    switchChannel(channels[i]);
    //Set MPU6050 to Measuring Mode
    Wire.beginTransmission(ACC);
    Wire.write(0x6B); //Access Power Register
    Wire.write(0x00); //Write for Measuring mode
    Wire.endTransmission(true);
    delay(10);
  }    
}

void Reader::readChannels()
{
 Serial.println("Scanning Channels");

  //Loop through possible channels
  for(uint8_t t = 0; t < 8; t++)
  {
      switchChannel(t);
      Serial.print("TCA Port #"); Serial.println(t);

      //Search for all I2C devices connected to bus (1 I2C bus can hold 128 devices)
      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == MUX) continue; //Avoid conflict with MUX

        Wire.beginTransmission(addr); 

        if (!Wire.endTransmission()) { //If Success
          Serial.print("Found I2C 0x");  Serial.println(addr,HEX); //Print addr in HEX
        }
      }
  }
  Serial.println("\ndone");
}

float* Reader::readValues()
{
  //Loop through all accelerometers
  for(int i = 0; i < 4; i++)
  {
    //Switch I2C Channel
    switchChannel(channels[i]);
    //Communicate to ACC in Channel
    Wire.beginTransmission(ACC);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(ACC, 6, true); //6 Values, 3 axes (X,Y,Z) * 2 parameters of each axis(X,Y)
 
    //Fill in Y, X, Z to array
    for(int j = 0; j < 3; j++)
    {
      reading[j] = readAccValue() + calibrationValues[i][j] * multiplicationValues[i][j];
    }
    
    //Roll & Pitch formula is derived by multiplying the scalar of Accelerometer values to the
    //3D Rotation Matrix then solve for the formula of the 2 angles, roll & pitch
    float roll = atan(reading[0]/ sqrt(pow(reading[1], 2) + pow(reading[2], 2))) * 180/PI;
    values[i * 2] = roll;
    float pitch = atan(-1 * reading[2]/ sqrt(pow(reading[1], 2) + pow(reading[0], 2))) * 180/PI;
    values[i * 2 + 1] = pitch;
    //Wire.endTransmission();
  }

  return values;
}

//Switch Channel of MUX
// channel - Channel number (0-7)
void Reader::switchChannel(int channel)
{
  Wire.beginTransmission(MUX);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

//Reads Accelerometer value
float Reader::readAccValue()
{
  //Accelerometer value is 10 bits but can only send 8 bits at a time, 
  //so 1st Wire.read() is 1st 8 bits, then 2nd Wire.read() is for the last 2 bits
  float value = Wire.read() << 8 | Wire.read();
  return value/16384; //To limit range to +- 2g
}

char* Reader::getSerialString()
{
  memset(serialString, 0, sizeof(serialString)); //Clean serial String to ""
  //Convert to serial string
  for(int i = 0; i < 8; i++)
  {
    appendFloat(values[i], serialString);
    strcat(serialString, ",");
  }
  return serialString;
}

//Trims the white spaces of string
void Reader::trimCh(char *str)
{
  //Find 1st space
  char *p = strchr(str, ' ');
  if(p) *p = 0; //Set to end pointer
}

//Appends float to char[]
void Reader::appendFloat(float value, char* string)
{
   //Get (3 max whole number with 2 decimal point value (6 bytes) + 
   // '-' in case of negative + end point = 8 bytes
   char valueStr[8];
   dtostrf(value, -7, 2, valueStr); //Convert float to char[]
   trimCh(valueStr);                //Trim extra spaces
   strcat(string, valueStr);        //Concat string
}
