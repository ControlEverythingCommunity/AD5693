// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5693
// This code is designed to work with the AD5693_I2CDAC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Digital-Analog?sku=AD5693_I2CDAC#tabs-0-product_tabset-2

#include<Wire.h>

// AD5693 I2C address is 0x4C(76)
#define Addr 0x4C

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[2] = {0x80, 0x00};

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select DAC and input register
  Wire.write(0x30);
  // Write data = 0x8000(32768)
  // data msb = 0x80
  Wire.write(data[0]);
  // data lsb = 0x00
  Wire.write(data[1]);
  // Stop I2C transmission
  Wire.endTransmission();

  // Convert the data, Vref = 5 V
  float voltage = (((data[0] * 256) + (data[1])) / 65536.0) * 5.0;

  // Output data to serial monitor
  Serial.print("Voltage : ");
  Serial.print(voltage);
  Serial.println(" V");
  delay(500);
}

