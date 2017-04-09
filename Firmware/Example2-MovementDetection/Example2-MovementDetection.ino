/*
  AK9752 Human Presence and Movement Sensor Example Code
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 10th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Takes an average of readings at startup. When a difference is detected, a
  human is present; determine which quadrants are sensing the human.

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

int ir1, ir2, ir3, ir4, temperature;
#define AVERAGE_AMOUNT 64
long irAverages[4];

void setup()
{
  Serial.begin(9600);
  Serial.println("AK9750 Read Example");

  Wire.begin();

  //Turn on sensor
  if (ak9750Setup() == false)
  {
    Serial.println("Device not found. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("Taking readings, please wait");

  for (byte x = 0 ; x < AVERAGE_AMOUNT ; x++)
  {
    while (!dataAvailable()) delay(1); //Wait for new data to be read
    irAverages[0] += getIR1();
    irAverages[1] += getIR2();
    irAverages[2] += getIR3();
    irAverages[3] += getIR4();
    refreshData(); //Read dummy register after new data is read
  }
  for (byte x = 0 ; x < 4 ; x++) irAverages[x] /= AVERAGE_AMOUNT;

  Serial.println("AK9750 Human Presence Sensor online");
}

void loop()
{
  if (dataAvailable())
  {
    ir1 = abs(getIR1() - irAverages[0]);
    ir2 = abs(getIR2() - irAverages[1]);
    ir3 = abs(getIR3() - irAverages[2]);
    ir4 = abs(getIR4() - irAverages[3]);
    float tempF = getTemperatureF();

    refreshData(); //Read dummy register after new data is read

    int averageIR = (ir1 + ir2 + ir3 + ir4) / 4;

    if (averageIR > 100)
    {
      Serial.print("Human present: ");
      //Try to figure out which sensors are triggering
      if (ir1 > 100) Serial.print("Down ");
      if (ir2 > 100) Serial.print("Left ");
      if (ir3 > 100) Serial.print("Right ");
      if (ir4 > 100) Serial.print("Up ");
    }
    else
    {
      Serial.print("Nothing detected");      
    }

    Serial.println();


    //Note: The observable area is shown in the silkscreen.
    //If sensor 2 increases first, the human is on the left
    /*Serial.print("1:DWN[");
    Serial.print(ir1);
    Serial.print("] 2:LFT[");
    Serial.print(ir2);
    Serial.print("] 3:UP[");
    Serial.print(ir3);
    Serial.print("] 4:RGH[");
    Serial.print(ir4);
    Serial.print("] AVG[");
    Serial.print(averageIR);
    Serial.print("] tempF[");
    Serial.print(tempF);
    Serial.print("] millis[");
    Serial.print(millis());
    Serial.print("]");
    Serial.println();*/
  }

  delay(100); //Wait for next reading
}


