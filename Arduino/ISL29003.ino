// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ISL29003
// This code is designed to work with the ISL29003_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Light?sku=ISL29003_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// ISL29003 I2C address is 0x44(68)
#define Addr 0x44

void setup()
{ 
  // Initialise I2C communication
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select command register
  Wire.write(0x00);
  // Select normal operation  
  Wire.write(0x80);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x01);
  // Set range = 64000 lux
  Wire.write(0x0C);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[2];
  // Start I2C Transmission
  Wire.beginTransmission(Addr); 
  // Select data register
  Wire.write(0x04);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // luminance lsb, luminance msb
  if(Wire.available() == 2)
  { 
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  delay(300);

  // Convert the data
  float luminance = (data[1] * 256) + data[0];
  
  // Output to the serial monitor
  Serial.print("Ambient Light luminance : ");
  Serial.println(luminance);
  delay(300);
}

