#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "nokia_lcd.h"

// Now with big fonts printBigWord()
// Fonts arrays go now to the flash memory (PROGMEM)

// http://excamera.com/sphinx/article-compression.html#compression
// fajne: https://github.com/das-labor

int xRAM;
int yRAM;

int pos;
uint8_t *pcData;

void Delay_MS(uint16_t dMS) {
	while (dMS--) {
		_delay_loop_2(2000);
	}
}

uint8_t SPI_MasterTransmit(unsigned char cByte) {
	SPDR = cByte;
	while (!(SPSR & (1 << SPIF)))
		// czekaj az bajt przeslany
		;
	return SPDR;
}

void N5110_WriteByte(uint8_t cByte, uint8_t cCommand) {
	N5110_CE_CLR;
	if (cCommand == 0) {
		N5110_DC_CLR;
	} else {
		N5110_DC_SET;
	}
	SPI_MasterTransmit(cByte);
	N5110_CE_SET;
}

void N5110_Clear(void) {
	uint16_t i;

	N5110_WriteByte(0x80, 0);
	N5110_WriteByte(0x40, 0);
	N5110_WriteByte(0x80, 0);
	for (i = 0; i < 504; i++) {
		N5110_WriteByte(0x00, 1);
	}
}

void N5110_Init(void) {

	// Port init
	N5110_DDR = N5110_DDR | (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);

	// SPI_MasterInit: fosc/128
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);   // SPE: SPI Enable, MSTR: Master/Slave Select
	SPSR &= ~(1 << SPI2X);											// SPI2X: Double SPI Speed Bit, SPI speed: strona 167, tabela 72

	N5110_RST_CLR;
	Delay_MS(1);
	N5110_RST_SET;

	N5110_CE_CLR;
	Delay_MS(1);
	N5110_CE_SET;

	Delay_MS(1);
	N5110_WriteByte(0x21, 0);          // extended instruction set
	N5110_WriteByte(0xc3, 0);          // set VOP
	N5110_WriteByte(0x04, 0);          // set TCx (jak 4, 5, 7 to ekran czarny)
//	N5110_WriteByte(0x13, 0);          // bias system 1:48 (tym sie reguluje contrast)
	N5110_WriteByte(0x10, 0);		   // konrast wzrasta po podlaczeniu RS232/USB
	N5110_WriteByte(0x20, 0);          // basic instruction set
	N5110_Clear();
	N5110_WriteByte(0x0C, 0);          // display control normal mode
	N5110_CE_CLR;

	N5110_BL_SET;          			   // turn on the background light
}

void setPos(int pos) {
	if (pos - 420 >= 0) {
		yRAM = 5;
		xRAM = pos - 420;
	} else if (pos - 336 >= 0) {
		yRAM = 4;
		xRAM = pos - 336;
	} else if (pos - 252 >= 0) {
		yRAM = 3;
		xRAM = pos - 252;
	} else if (pos - 168 >= 0) {
		yRAM = 2;
		xRAM = pos - 168;
	} else if (pos - 84 >= 0) {
		yRAM = 1;
		xRAM = pos - 84;
	} else {
		yRAM = 0;
		xRAM = pos;
	}

	N5110_WriteByte(((yRAM) | (1 << 6)), 0);          // Y-bank
	N5110_WriteByte(((xRAM) | (1 << 7)), 0);          // X
}

void printChar(char ch) {
	char litera;
	uint8_t i;

	for (i = 0; i < 5; i++) {
		// litera = fonts[ch - 0x20][i];
		litera = pgm_read_byte(&fonts[ch - 0x20][i]);
		N5110_WriteByte(litera, 1);
	}
	N5110_WriteByte(0x00, 1);          // maly odstep
}

void printWord(char *bString) {
	char ch;
	while (*bString != 0) {
		ch = *bString++;
		printChar(ch);
	}
}


/**
 * gotoXY routine to position cursor
 * x - range: 0 to 84
 * y - range: 0 to 5
 */
void gotoXY(int x, int y) {
	N5110_WriteByte(0x80 | x, 0);          // Column.
	N5110_WriteByte(0x40 | y, 0);          // Row.
}


void printSmString(uint8_t x, uint8_t y, char *bString) {
	char ch;

	gotoXY(x, y);
	while (*bString != 0) {
		ch = *bString++;
		printChar(ch);
	}
}


void printBigString(uint8_t x, uint8_t y, char *bString) {
	uint8_t i;
	char ch;
	char *bString2;
	bString2 = bString;

	gotoXY(6 * x, y);
	while (*bString != 0) {
		ch = *bString++;
		for (i = 0; i < 11; i++) {
			// N5110_WriteByte(Terminal11x16[ch - 0x20][2 * i], 1);					// reading from RAM
			N5110_WriteByte(pgm_read_byte(&Terminal11x16[ch - 0x20][2 * i]), 1);          // reading from flash
		}
		N5110_WriteByte(0x00, 1);          // maly odstep
	}

	gotoXY(6 * x, y + 1);
	while (*bString2 != 0) {
		ch = *bString2++;
		for (i = 0; i < 11; i++) {
			// N5110_WriteByte(Terminal11x16[ch - 0x20][(2 * i) + 1], 1);
			N5110_WriteByte(pgm_read_byte(&Terminal11x16[ch - 0x20][(2 * i) + 1]), 1);
		}
		N5110_WriteByte(0x00, 1);          // maly odstep - nie czsza
	}
}

void N5110_RefreshRam(uint8_t *pcBuff) {
	uint16_t i;
	N5110_WriteByte(0x80, 0);
	N5110_WriteByte(0x40, 0);
	N5110_WriteByte(0x80, 0);
	for (i = 0; i < 504; i++) {
		N5110_WriteByte(*pcBuff++, 1);
	}
}

/* waits (pauses) for ms milliseconds (assumes internal clock at 8MHz) */
void WaitMs(unsigned int ms) {
	int i;

	while (ms-- > 0) {
		/* 8192 (8k) clock cycles for 1ms; each time through loop
		 is 5 cycles (for loop control + nop) */
		for (i = 0; i < 1638; ++i)
			asm("nop");
	}
}

void drawBox(void) {
	int j;
	for (j = 0; j < 84; j++)          // top
			{
		gotoXY(j, 0);
		N5110_WriteByte(0x01, 1);
	}

	for (j = 0; j < 84; j++)          //Bottom
			{
		gotoXY(j, 5);
		N5110_WriteByte(0x80, 1);
	}

	for (j = 0; j < 6; j++)          // Right
			{
		gotoXY(83, j);
		N5110_WriteByte(0xff, 1);
	}

	for (j = 0; j < 6; j++)          // Left
			{
		gotoXY(0, j);
		N5110_WriteByte(0xff, 1);
	}
}

