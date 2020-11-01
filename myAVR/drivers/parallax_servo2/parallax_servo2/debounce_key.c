
#include <avr/io.h>
#include "debounce_key.h"

#define KEY1 PINE4
#define KEY2 PINE5


// KEY2	KEY1	result
//	0	0		0xc3	0b11000011
//	0	1		0xd3	0b11010011
//	1	0		0xe3	0b11100011
//	1	1		0xf3	0b11110011
uint8_t checkButtonState(uint8_t button) {
	
	uint8_t state = 0;
	
	if(button == KEY1 || button == KEY2) {
		if((PINE & (1 << KEY1)) != 0) {			// KEY1 pressed
			state = 1;
		}
		else if((PINE & (1 << KEY2)) != 0) {	// KEY2 pressed
			state = 2;
		}
		else {
			state = 0;
		}
	}
	else {
		state = 0xff;
	}
	return state;
}


void init_debounce_key_interrupt(sense_mode_t sense_mode) {

	DDRE &= ~_BV(DDE4) & ~_BV(DDE5);		// Set PE4 (INT4) to input
	
	//	ISC40 = 0, ISC41 = 0:	low level
	//	ISC40 = 0, ISC41 = 1:	any change
	//	ISC40 = 1, ISC41 = 0:	falling edge
	//	ISC40 = 1, ISC41 = 1:	raising edge
	
	switch (sense_mode)
	{
		case SENSE_FALLING:
		EICRB |= _BV(ISC40);
		EICRB &= ~_BV(ISC41);
		
		EICRB |= _BV(ISC50);					// Set INT5 to interrupt on every level change
		EICRB &= ~_BV(ISC51);
		
		EIMSK |= _BV(INT4) | _BV(INT5) ;		// Enable INT4 and INT5 in the Externalinterruptregister
		break;
		
		case SENSE_RAISING:
		EICRB |= _BV(ISC40);
		EICRB |= _BV(ISC41);
		
		EICRB |= _BV(ISC50);
		EICRB |= _BV(ISC51);
		
		EIMSK |= _BV(INT4) | _BV(INT5) ;
		break;
		
		case SENSE_BOTH:
		EICRB &= ~_BV(ISC40);
		EICRB |= _BV(ISC41);
		
		EICRB &= ~_BV(ISC50);
		EICRB |= _BV(ISC51);
		
		EIMSK |= _BV(INT4) | _BV(INT5) ;
		break;
	}
}


