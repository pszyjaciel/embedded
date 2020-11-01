
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "bcd_7segment.h"

uint8_t position = 4;
uint8_t myValue = 0;

ISR(TIMER0_OVF_vect) {
	PORTH ^= _BV(PH1);
	
	position--;
	load_digit_paterns(position % 4, myTable[myValue % 4]);
	myValue++;
	}


int main(void)
{
	init_7_segment();
	timer0_init();
	sei();
	
	DDRH = _BV(PH1);						// used for LED7

	float myFloat = 0.001;
	display_7_segment(myFloat, 4);
	
	while(1)
	{
		myFloat = myFloat + 0.001;
		display_7_segment(myFloat, 4);		// prepare array
	
		_delay_ms(300);
	}
}