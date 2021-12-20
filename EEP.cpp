#include "EEP.h"

EEP::EEP(int CE, int WE, int OE)
{
	// These default ports are what I have preferred using for my board setup and I recommend if you don't need to use the other pins.
	if (BOARD == 1)
	{
		a1 = &PORTB;
		a2 = &PORTC;
		d1 = &PORTD;
		*(a1 - 1) |= 0x3F;
		*(a2 - 1) |= 0x3F;
	}
	else if (BOARD == 2)
	{
		a1 = &PORTA;
		a2 = &PORTC;
		d1 = &PORTK;
		*(a1 - 1) |= 0xFF;
		*(a2 - 1) |= 0xFF;
	}
	else
	{
		return
	}
	ce = CE;
	we = WE;
	oe = OE;
	digitalWrite(ce, HIGH);
	digitalWrite(oe, HIGH);
	digitalWrite(we, HIGH);
}

EEP::EEP(volatile uint8_t *A1, volatile uint8_t *A2, volatile uint8_t *D1, int CE, int WE, int OE)
{
	a1 = A1;
	a2 = A2;
	d1 = D1;
	// For the UNO, there are only 3 ports, with one having a fullset of eight pins. The other two ports have 6 pins each 
	// and are used for the memory address, giving a total of 12 bits for the address. 
	if (BOARD == 1)
	{
		*(a1 - 1) |= 0x3F;
		*(a2 - 1) |= 0x3F;
	}
	// The Mega has many pins/ports to offer and can provide all 15 bits for the memory address.
	else if (BOARD == 2)
	{
		*(a1 - 1) |= 0xFF;
		*(a2 - 1) |= 0xFF;
	}
	else
	{
		return;
	}
	ce = CE;
	we = WE;
	oe = OE;
	digitalWrite(ce, HIGH);
	digitalWrite(oe, HIGH);
	digitalWrite(we, HIGH);
}

void EEP::writeWord(uint8_t data, uint16_t address)
{
	digitalWrite(ce, LOW);
	digitalWrite(we, LOW);
	if (BOARD == 1)
	{
		if (address < MAXA1 && data < MAXD)
		{
			*(d1 - 1) |= 0xFF;
			*a1 |= (address & 0x003F);
			*a2 |= address >> 6;
			*d1 |= data;
		}
		else
		{
			return;
		}
	}
	if (BOARD == 2)
	{
		if (address < MAXA2 && data < MAXD)
		{
			*(d1 - 1) |= 0xFF;
			*a1 |= (address & 0x00FF);
			*a2 |= (address >> 8);
			*d1 |= data;
		}
		else
		{
			return;
		}
	}
	digitalWrite(we, HIGH);
	digitalWrite(ce, HIGH);
}

void EEP::writePage(uint8_t *data, uint8_t datasize, uint16_t start)
{
	if (BOARD == 1)
	{
		if (start + datasize > MAXA1 || datasize > 64)
		{
			return;
		}
	}
	if (BOARD == 2)
	{
		if (start + datasize > MAXA2 || datasize > 64)
		{
			return;
		}
	}
	*(d1 - 1) |= 0xFF;
	for (int i = 0; i < datasize; i++)
	{
		digitalWrite(ce, LOW);
		digitalWrite(we, LOW);
		if (BOARD == 1)
		{
			if (*(data+i) < MAXD)
			{
				*a1 |= (start+i & 0x003F);
				*a2 |= start+i >> 6;
				*d1 |= *(data+1);
			}
			else
			{
				return;
			}
		}
		if (BOARD == 2)
		{
			if (*(data+i) < MAXD)
			{
				*a1 |= (start+i & 0x00FF);
				*a2 |= (start+i >> 8);
				*d1 |= *(data+1);
			}
			else
			{
				return;
			}
		}
		digitalWrite(ce, HIGH);
		digitalWrite(we, HIGH);
	}
}

uint8_t EEP::readWord(uint16_t address)
{
	digitalWrite(ce, LOW);
	digitalWrite(oe, LOW);
	*(d1 - 1) |= 0x00;
	if (BOARD == 1)
	{
		if (address < MAXA1)
		{
			*a1 |= (address & 0x003F);
			*a2 |= address >> 6;
			return *d1;
		}
		else
		{
			return;
		}
	}
	if (BOARD == 2)
	{
		if (address < MAXA2)
		{
			*a1 |= (address & 0x00FF);
			*a2 |= (address >> 8);
			return *d1;
		}
		else
		{
			return;
		}
	}
	digitalWrite(oe, HIGH);
	digitalWrite(ce, HIGH);
}