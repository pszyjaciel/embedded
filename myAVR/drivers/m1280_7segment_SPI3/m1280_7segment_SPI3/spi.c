
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spi.h"


void spi_init() {

	// output pins for SPI
	DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
	DDR_SPI &= ~(1 << DD_MISO);
	
	PORT_SPI &= ~(1 << DD_SS); 
	
	// clock na fosc/128
	SPSR &= ~(1 << SPI2X);
	SPCR |= (1 << SPR1);
	SPCR |= (1 << SPR0);
	
	// enable SPI Interrupt
	SPCR |= (1 << SPIE);
	
	// MSTR: Master Select
	SPCR |= (1 << MSTR);
	
	// DORD: Data Order: MSB first
	//SPCR &= ~(1 << DORD);
	SPCR |= (1 << DORD);
	
	
	// CPOL: Clock Polarity
	SPCR |= (1 << CPOL);
	
	// CPHA: Clock Phase
	SPCR |= (1 << CPHA);
	
	// enable SPI
	SPCR |= (1 << SPE);
	
	SPDR = SPSR;
	
}





