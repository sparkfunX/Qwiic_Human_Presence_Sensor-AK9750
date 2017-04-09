/*
  AK9752 Human Presence and Movement Sensor Example Code
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 10th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Outputs the four IR readings and internal temperature.

  IR readings increase as warm bodies enter into the observable areas.

  Hardware Connections (Breakoutboard to Arduino):
  3.3V = 3.3V
  GND = GND
  SDA = A4
  SCL = A5

  Serial.print it out at 9600 baud to serial monitor.

  Available functions:
  int getIR1,2,3,4()
  void refreshData() - Must be called to trigger next read
  void setMode(byte) - See defines
  void setCutoffFrequency(byte) - See defines
  bool dataAvailable()
  bool dataOverrun()
  float getTemperature()
  float getTemperatureF()
  void softReset()

  To Write:
  setThreshold13 or 24 : IR1/3 or IR 2/4, upper, lower
  setInterrupts

*/

#include <Wire.h>

// Return statuses when dealing with I2C devices
typedef enum
{
  SENSOR_SUCCESS,
  SENSOR_ID_ERROR,
  SENSOR_I2C_ERROR,
  SENSOR_INTERNAL_ERROR
  //...
} status_t;

int ir1, ir2, ir3, ir4, temperature;

void setup()
{
  Serial.begin(9600);
  Serial.println("AK9750 Read Example");

  Wire.begin();

  //Turn on sensor
  status_t returnCode = ak9750Setup();
  if (returnCode != SENSOR_SUCCESS)
  {
    Serial.println("Device not found. Check wiring.");
    while (1);
  }

  Serial.println("AK9750 Human Presence Sensor online");
}

void loop()
{
  if (dataAvailable())
  {
    ir1 = getIR1();
    ir2 = getIR2();
    ir3 = getIR3();
    ir4 = getIR4();
    float tempF = getTemperatureF();

    refreshData(); //Read dummy register after new data is read

    //Note: The observable area is shown in the silkscreen.
    //If sensor 2 increases first, the human is on the left
    Serial.print("1:DWN[");
    Serial.print(ir1);
    Serial.print("] 2:LFT[");
    Serial.print(ir2);
    Serial.print("] 3:UP[");
    Serial.print(ir3);
    Serial.print("] 4:RGH[");
    Serial.print(ir4);
    Serial.print("] tempF[");
    Serial.print(tempF);
    Serial.print("] millis[");
    Serial.print(millis());
    Serial.print("]");
    Serial.println();
  }

  delay(1);
}
