/*
  AK9752 Human Presence and Movement Sensor Example Code
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 10th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Prints the 

  Hardware Connections (Breakoutboard to Arduino):
  3.3V = 3.3V
  GND = GND
  SDA = A4
  SCL = A5

  Serial.print it out at 9600 baud to serial monitor.

*/

#include <Wire.h>

unsigned int upValue; // current proximity reading
unsigned int averageValue;   // low-pass filtered proximity reading
signed int fa2;              // FA-II value;
signed int fa2Derivative;     // Derivative of the FA-II value;
signed int fa2DerivativeLast;     // Last value of the derivative (for zero-crossing detection)
signed int sensitivity = 50;  // Sensitivity of touch/release detection, values closer to zero increase sensitivity

#define LOOP_TIME 30  // loop duration in ms

// Touch/release detection
//#define EA 0.3  // exponential average weight parameter / cut-off frequency for high-pass filter
//#define EA 0.3  //Very steep
//#define EA 0.1  //Less steep
#define EA 0.05  //Less steep

void setup()
{
  Serial.begin(115200);
  Serial.println("AK9750 Read Example");

  Wire.begin();

  //Turn on sensor
  if (ak9750Setup() == false)
  {
    Serial.println("Device not found. Check wiring.");
    while (1); //Freeze!
  }

  upValue = getIR3(); //Get initial values
  averageValue = upValue;
  fa2 = 0;
  refreshData(); //Read dummy register after new data is read

  Serial.println("AK9750 Human Presence Sensor online");
}

void loop()
{
  unsigned long startTime = millis();

  while (!dataAvailable()) delay(1);

  upValue = getIR3(); //Get latest IR value
  refreshData(); //Read dummy register after new data is read

  fa2DerivativeLast = fa2Derivative;
  fa2Derivative = (signed int) averageValue - upValue - fa2;
  fa2 = (signed int) averageValue - upValue;

  //Turn on various variables to see how they respond on the graph
  //Serial.print(upValue);
  //Serial.print(",");
  //Serial.print(fa2);
  //Serial.print(",");
  Serial.print(fa2Derivative);
  Serial.print(",");

  sensitivity = 100;
  if ((fa2DerivativeLast < -sensitivity && fa2Derivative > sensitivity) || (fa2DerivativeLast > sensitivity && fa2Derivative < -sensitivity)) // zero crossing detected
  {
    if (fa2 < -sensitivity) // minimum
    {
      Serial.print(-1000); //Indicate entering presence
      Serial.print(",");
      //Serial.print("Entered view");
    }
    else if (fa2 > sensitivity) // maximum
    {
      Serial.print(1000); //Indicate exiting presence
      Serial.print(",");
      //Serial.print("Exited view");
    }
    else
    {
      Serial.print(0); //Indicate no movement
      Serial.print(",");
      //Serial.print("No Movement");
    }
  }
  else
  {
    Serial.print(0);
    Serial.print(",");
  }

  Serial.println();

  // Do this last
  averageValue = EA * upValue + (1 - EA) * averageValue;
  while (millis() < startTime + LOOP_TIME); // enforce constant loop time
}
