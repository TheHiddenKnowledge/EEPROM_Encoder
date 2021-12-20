/* 
	Created by Isaiah Finney.
	Feel free to use.
	This is a library designed to read, write, and manage the memory of Microchip's AT28C256-15PU 32 KB IC package.
	The chip can interface with the arduino Mega and Uno, but interfacing with the Uno will results in loss of storage capabilites.
	Port manipulation is used for this library so look at the arduino figures provided to see what pins correspond to the 
	correct ports.
*/
#pragma once
// Maximum address value for the Uno board configuration.
#define MAXA1 0x0FFF
// Maximum address value for the Mega board configuration.
#define MAXA2 0x7FFF
// Maximum data value.
#define MAXD 0xFF

#include <Arduino.h>
#if defined(ARDUINO_AVR_UNO)
	#define BOARD 1 
#elif defined(ARDUINO_AVR_MEGA2560)
	#define BOARD 2
#endif


class EEP
{
public:
	// Constructor for EEPROM class that sets the address and data ports to defaults values based on the inputted board.
	// This is prefered if the Arduino is only used to read and write to the EEPROM without any other application.
	EEP(int CE, int WE, int OE);
	// Alternative constructor that allows the user to define which ports are to be used for the device address and data I/O.
	// Note that some of the ports may interfere with pins already used for other applications.
	EEP(volatile uint8_t *A1, volatile uint8_t *A2, volatile uint8_t *D1, int CE, int WE, int OE);
	// Pointer to first address port.
	volatile uint8_t *a1;
	// Pointer to second address port.
	volatile uint8_t *a2;
	// Pointer to data I/O port.
	volatile uint8_t *d1;
	// Pin for chip enable.
	int ce;
	// Pin for write enable.
	int we;
	// Pin for output enable.
	int oe;
	// Method for writing one byte to the address provided.s
	void writeWord(uint8_t data, uint16_t address);
	// Method for writing a page (<= 64 bytes) starting from the address provided. Will not work if the datasize plus the
	// start address is greater than the largest memory address or the datasize is greater than 64 bytes.
	void writePage(uint8_t *data, uint8_t datasize, uint16_t start);
	// Method for reading one byte from the address provided.
	uint8_t readWord(uint16_t address);
};