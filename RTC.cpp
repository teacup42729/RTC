#include <RTC.h>
#include <Wire.h>

void RTC::begin(void)
{
	Wire.begin();
}

void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
	// sets time and date data to DS3231
	Wire.beginTransmission(DS_I2C_ADDRESS);
	Wire.write(0); // set next input to start at the seconds register
	Wire.write(decToBcd(second)); // set seconds
	Wire.write(decToBcd(minute)); // set minutes
	Wire.write(decToBcd(hour)); // set hours
	Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
	Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
	Wire.write(decToBcd(month)); // set month
	Wire.write(decToBcd(year)); // set year (0 to 99)
	Wire.endTransmission();
}

void readTime(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
	Wire.beginTransmission(DS_I2C_ADDRESS);
	Wire.write(0); // set DS3231 register pointer to 00h
	Wire.endTransmission();
	Wire.requestFrom(DS_I2C_ADDRESS, 7);
	// request seven bytes of data from DS3231 starting from register 00h
	*second = bcdToDec(Wire.read() & 0x7f);
	*minute = bcdToDec(Wire.read());
	*hour = bcdToDec(Wire.read() & 0x3f);
	*dayOfWeek = bcdToDec(Wire.read());
	*dayOfMonth = bcdToDec(Wire.read());
	*month = bcdToDec(Wire.read());
	*year = bcdToDec(Wire.read());
}

void readSRAM(byte address, byte *value)
{
	Wire.beginTransmission(DS_I2C_ADDRESS);
	Wire.write(address + 8);
	Wire.endTransmission();

	Wire.requestFrom(DS_I2C_ADDRESS, 1);
	*value = Wire.read();
}

void readSRAM(byte startAddress, byte values[]. int numberOfValues)
{
	Wire.beginTransmission(DS_I2C_ADDRESS);
	Wire.write(startAddress + 8);
	Wire.endTransmission();

	Wire.requestFrom(DS_I2C_ADDRESS, numberOfValues);
	for (int i = 0; i < numberOfValues; i++)
	{
		values[i] = Wire.read();
	}
}

void writeSRAM(byte address, byte value)
{
	Wire.beginTransmission(DS_I2C_ADDRESS);
	Wire.write(address + 8);
	Wire.write(value);
	Wire.endTransmission();
}

void writeSRAM(byte startAddress, byte values[], int numberOfValues)
{
	Wire.beginTransmission(DS_I2C_ADDRESS);
	Wire.write(startAddress + 8);
	for (int i = 0; i < numberOfValues; i++)
	{
		Wire.write(values[i]);
	}
	Wire.endTransmission();
}

byte decToBcd(byte val)
{
	return(((val / 10) * 16) + (val % 10));
}

byte bcdToDec(byte val)
{
	return(((val / 16) * 10) + (val % 16));
}