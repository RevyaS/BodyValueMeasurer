#include <Wire.h>

//CALIBRATION AREA
#define xOffset 0
#define yOffset 0
#define zOffset 0
//END OF CALIBRATION

const int MPU6050 = 0x68; //I2C address
float values[3];
char str[70] = "";
String base = "";

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  
  //Set MPU6050 to Measuring Mode
  Wire.beginTransmission(MPU6050);
  Wire.write(0x2D);   //Access Power Register
  Wire.write(8);      //Write for Measuring mode
  Wire.endTransmission();
  delay(10);
}

void loop() {
  Wire.beginTransmission(MPU6050); //Access ADXL345
  Wire.write(0x32); //Access value registers
  Wire.endTransmission(false); //End connection while retaining access
  Wire.requestFrom(MPU6050, 6, true); //2 for each axis, therefore 6
  values[1] = readWire() + xOffset; //1st 2 Wire.read() is for X
  values[0] = readWire() + yOffset; //Next 2 Wire.read() is for Y
  values[2] = readWire() + zOffset; //Last 2 Wire.read() is for Z

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
  return values/16384;
}

float trimCh(char *str)
{
  char *p = strchr(str, ' '); //Find 1st instance of space
  if(p) *p = 0; //Terminate
}
