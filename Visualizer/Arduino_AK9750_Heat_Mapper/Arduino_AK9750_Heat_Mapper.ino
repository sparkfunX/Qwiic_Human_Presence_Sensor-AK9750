/*
  AK9752 Human Presence and Movement Sensor Visualizer
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 10th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Outputs the four IR readings and internal temperature.

  Used in conjunction with Processing app to visualize the data on a computer.

  IR readings increase as warm bodies enter into the observable areas.

  Hardware Connections:
  Attach a Qwiic shield to your RedBoard or Uno.
  Plug the Qwiic sensor into any port.
  Serial.print it out at 9600 baud to serial monitor.
*/

#include <Wire.h>

#include "SparkFun_AK9750_Arduino_Library.h"

AK9750 movementSensor; //Hook object to the library

int ir1, ir2, ir3, ir4, temperature;

void setup()
{
  Serial.begin(9600);

  Wire.begin();

  //Turn on sensor
  if (movementSensor.begin() == false)
  {
    Serial.println("Device not found. Check wiring.");
    while (1);
  }
}

void loop()
{
  if (movementSensor.available())
  {
    ir1 = movementSensor.getIR1(); //Lower
    ir2 = movementSensor.getIR2(); //Left
    ir3 = movementSensor.getIR3(); //Upper
    ir4 = movementSensor.getIR4(); //Right
    float tempF = movementSensor.getTemperatureF();

    movementSensor.refresh(); //Read dummy register after new data is read

    //Note: The observable area is shown in the silkscreen.
    //If sensor 2 increases first, the human is on the left
    Serial.print(ir1);
    Serial.print(",");
    Serial.print(ir2);
    Serial.print(",");
    Serial.print(ir3);
    Serial.print(",");
    Serial.print(ir4);
    Serial.print(",");
    Serial.print(tempF);
    Serial.println();
  }

  delay(50);
}
