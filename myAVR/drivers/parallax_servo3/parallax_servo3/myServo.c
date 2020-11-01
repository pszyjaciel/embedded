
#include <avr/io.h>
#include "myServo.h"
// #include "myUtil.h"

void setPrescaler(uint16_t speed) {
	
	// datasheet s. 170
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
	}
}


void init_rc_servo() {
	
	TCCR1A |= (1 << COM1C1);			// (p. 167) in u:\ICT\6th_semester\hwpi1\docs\atmega1280_datasheet.pdf
	TCCR1A |= (1 << COM1C0);
	
	TCCR1B |= (1 << WGM13);				// mode 9, p. 148
	TCCR1B &= ~(1 << WGM12);
	TCCR1A &= ~(1 << WGM11);
	TCCR1A |= (1 << WGM10);
	
	setPrescaler(PRESCALER);			// KEY1 pressed: set the prescaller; released stop the timer
	
	OCR1A = CENTER;						// 19.2 Description p. 172
	OCR1C = TOP;
	TCNT0 = 0x00;						// start value
}


void rc_servo2(int8_t angle) {
	if((angle > -101) && (angle < 101)) {
		uint16_t value = ((((CENTER - MIN) * angle)/100) + CENTER);
		OCR1A = value;
	}
}

void rc_servo(int8_t percent) {
	if (percent > 0 && percent <= 100) {
		uint16_t value = MAX - (((MAX - MIN) * percent)/100);
		if ((value < MAX) || (value > MIN)) {
			OCR1A = value;
		}
	}
}
