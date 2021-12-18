#ifndef EEPROM_h
#define EEPROM_h

class EEPROM {
	public:
		EEPROM(int board, volatile byte* I1, volatile byte* O1, int CE, int WE, int OE);
		EEPROM(int board, volatile byte* I1, volatile byte* I2, volatile byte* O1, volatile byte* O2, int CE, int WE, int OE);
		volatile byte* in1;
		volatile byte* in2; 
		volatile byte* out1;
		volatile byte* out2; 
		int 
		int BOARD;
		void writeEEP(unsigned char data, unsigned short address);
		void readEEP(unsigned short address);
};