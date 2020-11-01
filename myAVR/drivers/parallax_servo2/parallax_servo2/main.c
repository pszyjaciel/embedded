// u:\ICT\6th_semester\hwpi1\projects\parallax_servo2\parallax_servo2.atsln
// http://www.ermicro.com/blog/?p=1971
// https://courses.cit.cornell.edu/ee476/FinalProjects/s2009/hh236_qc36/hh236_qc36/
// uses mode 15, timer: OC1C on PB7, 4x4 keyboard: S13/S9 for control, KEY1 turns on the timer
// http://www.atmel.com/webdoc/doxygenIntegrator/doxygenIntegrator.Invoke.html


#include <avr/io.h>
#include <avr/interrupt.h>
#include "debounce_key.h"
#include "rc_servo.h"


ISR(INT4_vect) {
	if (OCR1C < MAX) {
		OCR1C += 0x01;
	}
}

ISR(INT5_vect) {
	if (OCR1C > MIN) {
		OCR1C -= 0x01;
	}
}


int main(void)
{
	init_rc_servo();
	init_debounce_key_interrupt(SENSE_RAISING);
	sei();

	while(1)
	{
		asm("nop");
	}
}
