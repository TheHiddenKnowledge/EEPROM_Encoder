/* 
	Created by Isaiah Finney 
	Feel free to use 
	This is a library designed to read, write, and manage the memory of Microchip's AT28C256-15PU 32 KB IC package.
	The chip can interface with the arduino Mega and Uno, but interfacing with the Uno will results in loss of storage capabilites.
*/

#include "EEPROM.h"

// Constructors for the EEPROM class:
EEPROM::EEPROM(int board, int CE, int WE, int OE)
{
	BOARD = board;
	if (BOARD == 1)
	{
		a1 = &PORTB;
		d1 = &PORTD;
		da1 = a1 - 1;
		dd1 = d1 - 1;
	}
	if (BOARD == 2)
	{
		a1 = &PORTA;
		a2 = &PORTC;
		d1 = &PORTK;
		da1 = a1 - 1;
		da2 = a2 - 1;
		dd1 = d1 - 1;
	}
	else
	{
		return
	}
	ce = CE;
	we = WE;
	oe = OE;
}

EEPROM::EEPROM(int board, volatile byte *A1, volatile byte *D1, int CE, int WE, int OE)
{
	BOARD = board;
	if (BOARD == 1)
	{
		a1 = A1;
		d1 = D1;
		da1 = a1 - 1;
		dd1 = d1 - 1;
		ce = CE;
		we = WE;
		oe = OE;
	}
	else
	{
		return;
	}
}

EEPROM::EEPROM(int board, volatile byte *A1, volatile byte *A2, volatile byte *D1, int CE, int WE, int OE)
{
	BOARD = board;
	if (BOARD == 1)
	{
		a1 = A1;
		a2 = A2;
		d1 = D1;
		da1 = a1 - 1;
		da2 = a2 - 1;
		dd1 = d1 - 1;
		ce = CE;
		we = WE;
		oe = OE;
	}
	else
	{
		return;
	}
}

void EEPROM::writeEEP(unsigned char data, unsigned short address)
{
	digitalWrite(ce, LOW);
	digitalWrite(oe, HIGH);
	digitalWrite(we, LOW);
	if (BOARD == 1)
	{
		*da1 |= 0xFF;
		*dd1 |= 0xFF;
		*a1 |= (address & 0x000F);
		*d1 |= data;
	}
	if (BOARD == 2)
	{
		*da1 |= 0xFF;
		*da2 |= 0xFF;
		*dd1 |= 0xFF;
		*a1 |= (address & 0x00FF);
		*a2 |= (address >> 8);
		*d1 |= data;
	}
	digitalWrite(we, HIGH);
	digitalWrite(oe, HIGH);
	digitalWrite(ce, HIGH);
}

byte EEPROM::readEEP(unsigned short address)
{
	if (BOARD == 1)
	{
		*da1 |= 0xFF;
		*dd1 |= 0x00;
		*a1 |= (address & 0x000F);
		return *d1;
	}
	if (BOARD == 2)
	{
		*da1 |= 0xFF;
		*da2 |= 0xFF;
		*dd1 |= 0x00;
		*a1 |= (address & 0x00FF);
		*a2 |= (address >> 8);
		return *d1;
	}
}