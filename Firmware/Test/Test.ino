/*
  AK9752 Human Presence and Movement Sensor Example Code
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 10th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Read the TVOC and CO2 values from the SparkFun CSS811 breakout board

  A new sensor requires at 48-burn in. Once burned in a sensor requires
  20 minutes of run in before readings are considered good.

  Hardware Connections (Breakoutboard to Arduino):
  3.3V = 3.3V
  GND = GND
  SDA = A4
  SCL = A5

  Serial.print it out at 9600 baud to serial monitor.

  Available functions:
  void setMode(byte) - See defines
  bool dataAvailable()
  bool dataOverrun()
  int getIR1()
  float getTemperature()
  void refreshData()
  void softReset()

  To Write:
  getAll() //Reads all four channels and refreshes data

  setEFC - filter freq in ECNTL1
  setThreshold13 or 24 : IR1/3 or IR 2/4, upper, lower
  setInterrupts
  Mode/FC setting?

*/

#include <Wire.h>

#define AK9750_ADDR 0x64 //7-bit unshifted default I2C Address

//Register addresses
#define AK9750_ST1 0x05

void setup()
{
  Serial.begin(9600);
  Serial.println("AK9750 Read Example");

  Wire.begin();

  byte deviceID = readRegister(0x01);

  Serial.print("deviceID: ");
  Serial.println(deviceID);
  if (deviceID != 0x13)
  {
    Serial.println("Failed to find part");
    while(1);
  }

  Serial.println("Device found!");
}

void loop()
{

}

//Sets up the sensor for constant read
//Returns false if sensor does not respond
boolean ak9750Setup(void)
{

}

//Reads from a give location
byte readRegister(byte location)
{
  Wire.beginTransmission(AK9750_ADDR);
  Wire.write(location);
  Wire.endTransmission();

  Wire.requestFrom(AK9750_ADDR, 1);

  if (!Wire.available()) return (255);

  return (Wire.read());
}

