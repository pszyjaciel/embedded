/*
 * bcd_7segment.c
 *
 * Created: 4/29/2015 9:25:23 PM
 *  Author: root
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "bcd_7segment.h"


 const uint8_t patterns[] =  {	0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0,
 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e };


void load_shift_register(uint8_t pattern) {
	uint8_t value;
	uint8_t count = 8;
	
	do {
		value = pattern;
		value = value & 0b00000001;
		if(value == 0) {
			PORTB &= ~(1 << DS);	// send 0;
		}
		else {
			PORTB |= 1 << DS;		// send 1;
		}
		
		pattern = pattern >> 1;
		
		PORTB |= 1 << SHCP;			// pulse SHCP
		asm("nop");
		asm("nop");
		PORTB &= ~(1 << SHCP);
		
		count--;					// 8 bits
		
	} while (count > 0);
}


void load_digit_paterns(uint8_t digit, uint8_t pattern) {
	
	load_shift_register(pattern);
	
	PORTL = 0x00;
	
	PORTK |= 1 << STCP;			// strobe storage register
	asm("nop");
	asm("nop");
	PORTK &= ~(1 << STCP);
	
	digit = digit % 4;
	PORTL |= 1 << digit;
}


// for snprintf to work as expected, some flags must be added for the linker:
// -Wl,-u,vfprintf -lprintf_flt -lm
// http://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaa3b98c0d17b35642c0f3e4649092b9f1
	
void display_7_segment(float value, uint8_t no_of_decimals) {

	char myStrTable[20];
	snprintf(myStrTable, 20, "%f", value);			// convert from float to string

	uint8_t j;
	uint8_t k = 0;
	static uint8_t myPointer;
	static uint8_t myValue;						// is private

	for (j = 0; j < 5; j++) {
		if (myStrTable[j] == 0x2e) {			// is it a dot?

			// take the previous digit
			j--;
			k--;
			myPointer = myStrTable[j] - 0x30;
			myValue = patterns[myPointer];
			myTable[k] = myValue + 1;			// add the dot (DP is LSB)
			j++;
			k++;
		}

		else {
			myPointer = myStrTable[j] - 0x30;	// 0x30: from ascii to decimal
			myValue = patterns[myPointer];
			myTable[k] = myValue;				// update the BCD-table
			k++;
		}
	}
}


void timer0_init() {
	
	TIMSK0 = (1 << TOIE0);				// turns on the interrupts 
	TIFR0 |= (1 << TOV0);				// .. on overflow
	TCNT0 = 0x0000;
	
	// start timer0 with /256 prescaler (p. 161)
	TCCR0B |= (1 << CS02);
	TCCR0B &= ~(1 << CS01);
	TCCR0B &= ~(1 << CS00);
}


void init_7_segment() {
	
	DDRB = (1 << SHCP) | (1 << DS) | (1 << MR);
	DDRK = 1 << STCP;
	DDRL = (1 << A) | (1 << B) | (1 << C) | (1 << D);
	
	PORTB &= ~(1 << MR);		// reset 74595
	asm("nop");
	asm("nop");
	asm("nop");
	PORTB |= 1 << MR;
}