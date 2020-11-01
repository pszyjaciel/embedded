
// servo test program now with phase correct

#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>
#include "myServo.h"
// #include "myUart.h"
// #include "myUtil.h"


#define DEBOUNCE_TIME 25

#define KEYPAD_PORT PORTJ
#define KEYPAD_DDR  DDRJ
#define KEYPAD_PIN  PINJ


void checkStartButton() {

	// KEY2	KEY1	result
	//	0	0		0xc3	0b11000011
	//	0	1		0xd3	0b11010011
	//	1	0		0xe3	0b11100011
	//	1	1		0xf3	0b11110011
	
	if((PINE & (1 << PINE4)) != 0) {	// button pressed
		if ((TCCR1B & 0x07) == 0)		// if prescaler is 0
		{
			setPrescaler(PRESCALER);
		}
	}
	else {								// button released
		setPrescaler(0);
	}
}


void init_keyboard() {
	KEYPAD_DDR |= _BV(PJ0) | _BV(PJ1) | _BV(PJ2) | _BV(PJ3);		// outputs
	KEYPAD_DDR &= ~_BV(PJ4) & ~_BV(PJ5) & ~_BV(PJ6) & ~_BV(PJ7);	// inputs
	
	KEYPAD_PORT &= ~_BV(PJ0) & ~_BV(PJ1) & ~_BV(PJ2) & ~_BV(PJ3);	// outputs 0-3 to 0
	KEYPAD_PORT |= _BV(PJ4) | _BV(PJ5) | _BV(PJ6) | _BV(PJ7);		// pull up 4-7 to 1
};


static uint8_t getKey() {
	uint8_t c, d;
	for(c = 0; c < 4; c++) {			 // Count four columns
		KEYPAD_PORT = ~(1 << c);	     // Shift across four bits
		_delay_ms(DEBOUNCE_TIME);
		d = KEYPAD_PIN;					 // Sample the port for keypress

		if ((d | 0x0F) != 0xFF) {
			_delay_ms(DEBOUNCE_TIME);
			d = KEYPAD_PIN;
			// PORTH = d;
		}
	}
	return d;
}


int main(void)
{
	int8_t i = 0;

	DDRB |= (1 << PB7);					// OC1C as output
	DDRH = 0xff;						// LEDs
	DDRE &= ~_BV(DDE4) & ~_BV(DDE5);	// debounced keys
	
	init_rc_servo();
	init_keyboard();
	// USART_init();

	checkStartButton();
	
	for (i = 1; i < 100; i += 1) {
		rc_servo(i);				// move to the right (percentage function)
		_delay_ms(5);
	}
	_delay_ms(1500);
	
	for (i = 100; i > 0; i -= 1) {
		rc_servo(i);				// move to the left
		_delay_ms(5);
	}
	
	_delay_ms(1500);
	rc_servo2(0);					// move to the center
	
	while(1)
	{
		checkStartButton();			// KEY1 pressed: enable the timer, else disable it
		
		uint8_t d = getKey();		// get the S9 or S13 from 4x4 keyboard
		PORTH = d;
		
		if(d == 0xd7) {				// S9
			i+= 5;
			rc_servo2(i);			// call the angle_function
		}
		
		else if(d == 0xe7) {		// S13
			i-= 5;
			rc_servo2(i);
		}
	}
}
