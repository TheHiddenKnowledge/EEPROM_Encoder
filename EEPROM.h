#ifndef EEPROM_h
#define EEPROM_h
class EEPROM {
	public:
		EEPROM(int B);
		int BOARD;
		void setup(int B);
		void writeEEP(unsigned char data, unsigned short address);
		void readEEP(unsigned short address);
};