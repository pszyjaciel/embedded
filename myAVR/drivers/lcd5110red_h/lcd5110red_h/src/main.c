/*
Nokia5110 Red Display works on SPI (PortB)

Connections for Atmega 2560, PortB SPI is a MUST:
//1: VCC (+3.3 up to 5.0)	czerwony//2: GND			czarny//3: SCE - PB6		brazowy//4: RST - PB5		pomarancz//5: D/C - PB4		zolty//6: DN(MOSI) - PB2	niebieski    pin21//7: SCLK - PB1		fioletowy	 pin20//8: LED - PB3		bialy
//					zielony nie podlaczony


PORTL:
OC5B PL4 - patrz Timer3

implicit declaration jest gdy jest zla kolejnosc funkcji
funkcja ktora wywoluje inna MUSI byc na spodzie, a przed nia funkcja wywolywana

*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "nokia_lcd.h"
#include "speaker.h"

volatile uint16_t T2COMPA = 0;
volatile uint16_t T0OVF = 0;
volatile uint16_t T1COMPA = 0;


// https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
void Timer1_Init(void) {
	// 16bit
	OCR1A = 0x3D08;        // wartosc do porownania
	TCCR1B |= (1 << WGM12);
	TIMSK1 = (1 << OCIE1A);        // Timer/Counter1, Overflow Interrupt Enable
	TCCR1B |= (1 << CS12) | (1 << CS10);  // TCCR1B – Timer/Counter 1 Control Register B
}

ISR(TIMER1_COMPA_vect) {
	T1COMPA++;
	if (T1COMPA > 59) {
		T1COMPA = 0;
	}
}

void Timer2_Init(void) {			// 8 bit, Overflow
	TCNT2 = 0;						// 8bit, CNC
	TCCR2A |= (1 << WGM21);			// Mode CTC
	TCCR2B = (1 << CS22) | (1 << CS20);        // clk/1024
	OCR2A = 0xFF;					// wartosc do porownania
	TIMSK2 = (1 << OCIE2A);		    // przerwanie gdy Compare Match
}

ISR(TIMER2_COMPA_vect) { /* Timer/Counter2 Compare Match A */
	T2COMPA++;
	asm("nop");
}

void Timer3_Init(void) {
	// 16bit
	OCR5A = 0x1D08;        // wartosc do porownania
	TCCR5A |= (1 << COM5B0);
	//	TCCR5A |= (1 << WGM51);
	TCCR5B |= (1 << WGM52);			// Mode: CTC (p. 148)
	TCCR5B |= (1 << CS50);
}

// 16bit counters p. 136

int main(void) {

	Port_Init();
	SPI_MasterInit();
	Timer0_Init();
	Timer1_Init();
	Timer2_Init();
	//	Timer3_Init();
	Speaker_Init();
	N5110_Init();

	sei();

	uint8_t val, oldval = 0, i = 0, j = 0, k = 0;
	char ch, shape;
	int nPos = 419;
	char buffer[65];

	while (1) {
		PORTA = PINC;
		
		setPos(0);
		itoa(OCR5A, buffer, 10);
		printWord("OCR5A: ");
		printWord(buffer);
		
		setPos(84);
		itoa(T1COMPA, buffer, 10);
		printWord("T1COMPA: ");
		printWord(buffer);

		setPos(84 + 84);
		itoa(T2COMPA, buffer, 16);
		printWord("T2COMPA: ");
		printWord(buffer);

		setPos(84 + 84 + 84);
		val = PINC & 0b00001000;        // czy wcisniety SW2 (PD3)
		if (val == 0) {
			if (oldval != T1COMPA) {
				oldval = T1COMPA;
				OCR0A += 0x10;        // zwieksz jasnosc
				OCR5A += 0x0400;
			}
			
			else {
				OCR5A += 0xffff;
			}
		}

		itoa(OCR0A, buffer, 16);
		printWord("OCR0A: ");
		printWord(buffer);

		setPos(84 + 84 + 84 + 84);
		printWord("SW3 Backlight");


	}
}
