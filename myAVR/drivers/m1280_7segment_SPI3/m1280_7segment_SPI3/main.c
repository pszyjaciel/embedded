/*
This BCD driver use the SPI functionality to display a float value on LCD.
Function display_7_segment() prepare an array of patterns to display.
The main loop calls displayFloat() with a float value as parameter.
The displayFloat() will call the display_7_segment() ONLY IF SPI is ready 
to take the next byte.
Finally the ISR(SPI_STC_vect) send these patterns to the LCD one digit at a time.

The timing is to be find in this file: osci.png 
The SPI period is set to ~150usec.
The displayFloat() costs 100usec of uC-time.
*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "bcd_7segment.h"
#include "spi.h"

uint8_t spiReady = 0;
uint8_t state = 1;


ISR(SPI_STC_vect) {

	PORTL = 0x00;				// kathods off
	
	PORTK |= 1 << STCP;			// PK3: pin12 strobe storage register
	asm("nop");
	asm("nop");
	asm("nop");
	PORTK &= ~(1 << STCP);

	if (state == 1)
	{
		SPDR = myBCDTable[2];
		PORTL |= 1 << D;
		state = 2;
	}
	else if (state == 2)
	{
		SPDR = myBCDTable[1];
		PORTL |= 1 << C;
		state = 3;
	}
	else if (state == 3)
	{
		SPDR = myBCDTable[0];
		PORTL |= 1 << B;
		state = 4;
		spiReady = 1;
	}
	else if (state == 4)
	{
		SPDR = myBCDTable[3];
		PORTL |= 1 << A;		// kathode on
		state = 1;				// change the state to next digit
	}
}

void displayFloat(float myFloat)
{
	if (spiReady == 1)
	{
		if ((SPSR & (1 << SPIF)) == 0)			// checks to see if the SPI bit is clear
		{
			myFloat = myFloat + 0.001;
			display_7_segment(myFloat, 4);		// prepare array
			spiReady = 0;
		}
	}
}

int main(void)
{
	init_7_segment();
	spi_init();								// initialize spi
	sei();
	
	DDRH = 0xff;							// LEDs
	DDRB |= (1 << 6) | (1 << 7);			// osci
	PORTH = 0x00;							// LEDs off

	float myFloat = 0.001;
	display_7_segment(myFloat, 4);

	while (1) {
		myFloat = myFloat + 0.001;
		displayFloat(myFloat);
		
		_delay_ms(100);
	}
}

