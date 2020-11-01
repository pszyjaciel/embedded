
#include <avr/io.h>
#include <stdio.h>

#include "spi.h"
#include "bcd_7segment.h"


 const uint8_t patterns[] =  {	0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0,
 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e };


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
			myBCDTable[k] = myValue + 1;			// add the dot (DP is LSB)
			j++;
			k++;
		}

		else {
			myPointer = myStrTable[j] - 0x30;	// 0x30: from ascii to decimal
			myValue = patterns[myPointer];
			myBCDTable[k] = myValue;				// update the BCD-table
			k++;
		}
	}
}

void init_7_segment() {
	
	DDRK = 1 << STCP;
	DDRL = (1 << A) | (1 << B) | (1 << C) | (1 << D);	// 4 katody
	
	PORTB &= ~(1 << DD_MISO);		// reset 74595 (sygnal MR)
	asm("nop");
	asm("nop");
	asm("nop");
	PORTB |= 1 << DD_MISO;
}
