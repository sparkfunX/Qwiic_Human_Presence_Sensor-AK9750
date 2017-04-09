#define AK9750_ADDR 0x64 //7-bit unshifted default I2C Address

//Register addresses
#define AK9750_WIA2 0x01 //Device ID
#define AK9750_ST1 0x05
#define AK9750_IR1 0x06
#define AK9750_IR2 0x08
#define AK9750_IR3 0x0A
#define AK9750_IR4 0x0C
#define AK9750_TMP 0x0E
#define AK9750_ST2 0x10 //Dummy register
#define AK9750_ETH13H 0x11
#define AK9750_ETH13L 0x13
#define AK9750_ETH24H 0x15
#define AK9750_ETH24L 0x17
#define AK9750_EHYS13 0x19
#define AK9750_EHYS24 0x1A
#define AK9750_EINTEN 0x1B
#define AK9750_ECNTL1 0x1C
#define AK9750_CNTL2 0x19

//Valid sensor modes - Register ECNTL1
#define MODE_STANDBY 0b000
#define MODE_EEPROM_ACCESS 0b001
#define MODE_SINGLE_SHOT 0b010
#define MODE_0 0b100
#define MODE_1 0b101
#define MODE_2 0b110
#define MODE_3 0b111

//Valid digital filter cutoff frequencies
#define FREQ_0_3HZ 0b000
#define FREQ_0_6HZ 0b001
#define FREQ_1_1HZ 0b010
#define FREQ_2_2HZ 0b011
#define FREQ_4_4HZ 0b100
#define FREQ_8_8HZ 0b101

//Sets up the sensor for constant read
//Returns false if sensor does not respond
boolean ak9750Setup(void)
{
  byte deviceID = readRegister(AK9750_WIA2);

  if (deviceID != 0x13) return (false); //Device ID should be 0x13

  setMode(MODE_0); //Set to continuous read

  setCutoffFrequency(FREQ_8_8HZ); //Set output to fastest, with least filtering

  refreshData(); //Read dummy register after new data is read

  return (true);
}

//Returns the decimal value of sensor channel
int getIR1()
{
  return (readRegister16(AK9750_IR1));
}
int getIR2()
{
  return (readRegister16(AK9750_IR2));
}
int getIR3()
{
  return (readRegister16(AK9750_IR3));
}
int getIR4()
{
  return (readRegister16(AK9750_IR4));
}

//This reads the dummy register ST2. Required after
//reading out IR data.
void refreshData()
{
  readRegister(AK9750_ST2); //Do nothing but read the register
}

//Returns the temperature in C
float getTemperature()
{
  int value = readRegister16(AK9750_TMP);
  value >>= 6; //Temp is 10-bit. TMPL0:5 fixed at 0

  float temperature = 26.75 + (value * 0.125);
  return (temperature);
}

//Returns the temperature in F
float getTemperatureF()
{
  float temperature = getTemperature();
  temperature = temperature * 1.8 + 32.0;
  return (temperature);
}

//Set the mode. Continuous mode 0 is favored
void setMode(byte mode)
{
  if (mode > MODE_3) mode = MODE_0; //Default to mode 0
  if (mode == 0b011) mode = MODE_0; //0x03 is prohibited

  //Read, mask set, write
  byte currentSettings = readRegister(AK9750_ECNTL1);
  currentSettings &= 0b11111000; //Clear Mode bits
  currentSettings |= mode;
  writeRegister(AK9750_ECNTL1, currentSettings);
}

//Set the cutoff frequency. See datasheet for allowable settings.
void setCutoffFrequency(byte frequency)
{
  if (frequency > 0b101) frequency = 0; //Default to 0.3Hz

  //Read, mask set, write
  byte currentSettings = readRegister(AK9750_ECNTL1);
  currentSettings &= 0b11000111; //Clear EFC bits
  currentSettings |= (frequency << 3); //Mask in
  writeRegister(AK9750_ECNTL1, currentSettings); //Write
}

//Checks to see if DRDY flag is set in the status register
boolean dataAvailable()
{
  byte value = readRegister(AK9750_ST1);
  return (value & (1 << 0)); //Bit 0 is DRDY
}

//Checks to see if Data overrun flag is set in the status register
boolean dataOverrun()
{
  byte value = readRegister(AK9750_ST1);
  return (value & 1 << 1); //Bit 1 is DOR
}

//Does a soft reset
void softReset()
{
  writeRegister(AK9750_CNTL2, 0xFF);
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

//Write a value to a spot
void writeRegister(byte location, byte val)
{
  Wire.beginTransmission(AK9750_ADDR);
  Wire.write(location);
  Wire.write(val);
  Wire.endTransmission();
}

//Reads a two byte value from a consecutive registers
int readRegister16(byte location)
{
  Wire.beginTransmission(AK9750_ADDR);
  Wire.write(location);
  Wire.endTransmission(); //Send a restart command. Do not release bus.

  Wire.requestFrom(AK9750_ADDR, 2);

  int data = Wire.read();
  data |= (Wire.read() << 8);

  return (data);
}

