/* 
	Created by Isaiah Finney 
	Feel free to use 
	This is a library designed to read, write, and manage the memory of Microchip's AT28C256-15PU 32 KB IC package.
	The chip can interface with the arduino Mega and Uno, but interfacing with the Uno will results in loss of storage capabilites.
*/

#include "EEPROM.h"

// Constructor for the EEPROM class
void EEPROM::EEPROM(int b) {
	int BOARD = B 
}

void EEPROM::writeEEP(unsigned char data, unsigned short address) {
	if (BOARD == 1) {

	}
	if (BOARD == 2) {
		DDRA |= 0xFF;
		DDRC |= 0xFF;
		DDRK |= 0xFF;
		DDRG |= 0x03;
		PORTA |= (address & 0x00FF);
		PORTC |= (address >> 8);
		PORTG |= 0x01;
		PORTK |= data;
	}
}
unsigned char EEPROM::readEEP(unsigned short address) {
	if (BOARD == 1) {
		DDRD |= 0xFF;
		DDRB |= 0xF0;
		PORTD |= (address | 0x0F);
		PORTB |= (0x2<<4);
		return (PINB|0x0F);
	}
	if (BOARD == 2) {
		DDRA |= 0xFF;
		DDRC |= 0xFF;
		DDRK |= 0x00;
		DDRG |= 0X03;
		PORTA |= (address | 0x0F);
		PORTD |= (address >> 8);
		PORTG |= 0x02;
		return PINK;
	}	
}