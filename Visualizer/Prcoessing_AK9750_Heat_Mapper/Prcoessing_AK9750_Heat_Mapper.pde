/*
  Demo the four IR sensors on the AK9750 on a heat map
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 24th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This processing sketch demonstrates how to read the four IR values from the AK9750 and 
  display them in a four quadrant heat map.
  
  You'll need the AK9750 hooked up to an Arduino and running the "Arduino_AK9750_Heat_Mapper.ino" sketch. 
*/

import processing.serial.*;

Serial myPort;

float[] sensorValue = new float[4];

int windowX = 1000; //Make these values match the size() call in setup()
int windowY = 1000;

int ballSize = windowX / 2;

//Data comes in as:
//sensorValue[0] is lower
//sensorValue[1] is left
//sensorValue[2] is upper
//sensorValue[3] is right

int ballLocation0X = windowX / 2; //Lower
int ballLocation0Y = windowY / 4 * 3;

int ballLocation1X = windowX / 4; //Left
int ballLocation1Y = windowY / 2;

int ballLocation2X = windowX / 2; //Upper
int ballLocation2Y = windowY / 4;

int ballLocation3X = windowX / 4 * 3; //Right
int ballLocation3Y = windowY / 2;

void setup()
{
  size(1000, 1000); //Set this to whatever screen size you'd like

  //Initialize your serial port and set the baud rate to 9600
  myPort = new Serial(this, Serial.list()[2], 9600); //You may need to set your comm port to 0, 1, etc
  myPort.bufferUntil('\n');
}

void draw()
{
  background(0); //Clear screen

  //Draw the heat circles and color them based on incoming sensor values
  fill( int(sensorValue[0]), 0, 0 );
  ellipse(ballLocation0X, ballLocation0Y, ballSize, ballSize);

  fill( int(sensorValue[1]), 0, 0 );
  ellipse(ballLocation1X, ballLocation1Y, ballSize, ballSize);

  fill( int(sensorValue[2]), 0, 0 );
  ellipse(ballLocation2X, ballLocation2Y, ballSize, ballSize);

  fill( int(sensorValue[3]), 0, 0 );
  ellipse(ballLocation3X, ballLocation3Y, ballSize, ballSize);
}

//If there is incoming serial, parse it and load it into the sensorValue array
void serialEvent(Serial myPort) {

  String val = myPort.readStringUntil('\n');

  if (val != null) 
  {
    val = trim(val); //Trim whitespace and formatting characters
    println(val); //Print the incoming string for debugging

    String tempValues[] = split(val, ',');

    for (int x = 0; x < 4; x++)
    {
      //Convert the string into an int that is mapped
      //-200 to 400 works well but play with it
      sensorValue[x] = map(float(tempValues[x]), -200, 400, 0, 255);
    }

  }
}