#ifndef _RTC_H
#define _RTC_H

#include "Arduino.h"

#define DS_I2C_ADDRESS 0x68

class RTC
{
	public:

		void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
		void readTime(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year);

		void readSRAM(byte address, byte *value);
		void readSRAM(byte startAddress, byte values[], int numberOfValues);
		void writeSRAM(byte address, byte value);
		void writeSRAM(byte startAddress, byte values[], int numberOfValues);

	private:
		byte decToBcd(byte val);
		byte bcdToDec(byte val);
};

#endif
