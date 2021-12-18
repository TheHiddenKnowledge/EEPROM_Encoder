#ifndef EEPROM_h
#define EEPROM_h

#include <Arduino.h>
#include <io.h>

class EEPROM {
	public:
		EEPROM(int board, int CE, int WE, int OE);
		EEPROM(int board, volatile byte* A1, volatile byte* D1, int CE, int WE, int OE);
		EEPROM(int board, volatile byte* A1, volatile byte* A2, volatile byte* D1, int CE, int WE, int OE);
		volatile byte* a1;
		volatile byte* a2; 
		volatile byte* d1;
		volatile byte* da1;
		volatile byte* da2; 
		volatile byte* dd1;
		int ce;
		int we;
		int oe; 
		int BOARD;
		void writeEEP(unsigned char data, unsigned short address);
		void readEEP(unsigned short address);
};

#endif