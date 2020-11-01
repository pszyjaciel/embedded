/*! @file rc_servo.c
@brief Implementation of library to control the Parallax Servo.
@author Pawel Kramarz
@defgroup servo_module Parallax Servo Driver */

#include <avr/io.h>
#include "rc_servo.h"

void setPrescaler(uint16_t speed) {
	switch (speed)
	{
		case 0:									// no clock
		TCCR1B &= 0xf8;
		break;

		case 1:
		TCCR1B &= ~(1 << CS12) & ~(1 << CS11);
		TCCR1B |= (1 << CS10);
		break;
		
		case 8:
		TCCR1B &= ~(1 << CS12) & ~(1 << CS10);
		TCCR1B |= (1 << CS11);
		break;
		
		case 64:
		TCCR1B &= ~(1 << CS12);
		TCCR1B |= (1 << CS11) | (1 << CS10);
		break;

		case 256:
		TCCR1B |= (1 << CS12);
		TCCR1B &= ~(1 << CS11) & ~(1 << CS10);
		break;

		case 1024:
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TCCR1B &= ~(1 << CS11);
		break;
		
		default:
		TCCR1B &= 0xf8;
		break;
	}
}

void init_rc_servo() {

	DDRB |= (1 << PB7);					// OC1C as output
	
	TCCR1A |= (1 << COM1C1);			// Toggle OC1C on Compare Match
	TCCR1A &= ~(1 << COM1C0);			// (p. 167) in u:\ICT\6th_semester\hwpi1\docs\atmega1280_datasheet.pdf
	
	TCCR1B |= (1 << WGM13);				// mode 15, p. 148
	TCCR1B |= (1 << WGM12);
	TCCR1A |= (1 << WGM11);
	TCCR1A |= (1 << WGM10);
	
	setPrescaler(PRESCALER);
	
	OCR1A = TOP;						// period: 50Hz for prescaller 64, 19.2 Description p. 172
	OCR1C = CENTER;						// set the rotor to the center position
	TCNT1 = 0x0000;						// start value
}

void rc_servo(int8_t percent) {
	
	if((percent > -101) && (percent < 101)) {
		uint16_t value = ((((CENTER - MIN) * percent)/100) + CENTER);
		OCR1A = value;
	}
}
