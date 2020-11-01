
#include <avr/io.h>
#include <util/delay.h>


void init_keyboard() {
	// (columns) output bits 0-3
	DDRJ |= _BV(PJ0) | _BV(PJ1) | _BV(PJ2) | _BV(PJ3);		
	
	// (rows) input bits 4-7
	DDRJ &= ~_BV(PJ4) & ~_BV(PJ5) & ~_BV(PJ6) & ~_BV(PJ7);	
	
	// pull up for bits 4-7
	PORTJ |= _BV(PJ4) | _BV(PJ5) | _BV(PJ6) | _BV(PJ7);		
	}


uint8_t getKey() {

	// columns are controlled by 0, because of pull-up resistors on input pins.
	const uint8_t columns[] = { 0xf7, 0xfb, 0xfd, 0xfe };	// low nibble is pull up
	uint8_t row, col;

	for (row = 0; row < 4; row++)
	{
		_delay_ms(10);

		PORTJ = columns[row];				// 11110111, 11111011, 11111101, 11111110
		col = PINJ;							// read the column
		
		if ((col & 0xf0) != 0xf0)			// only hi-nibble counts
		{
			// print_hexByte(value);
			// print_hexByte(row);
			
			if (col == 0x77 && row == 0x00) {
				return 0x00;
			}
			else if (col == 0x7b && row == 0x01) {
				return 0x01;
			}
			else if (col == 0x7d && row == 0x02) {
				return 0x02;
			}
			else if (col == 0x7e && row == 0x03) {
				return 0x03;
			}
			else if (col == 0xb7 && row == 0x00) {
				return 0x04;
			}
			else if (col == 0xbb && row == 0x01) {
				return 0x05;
			}
			else if (col == 0xbd && row == 0x02) {
				return 0x06;
			}
			else if (col == 0xbe && row == 0x03) {
				return 0x07;
			}
			else if (col == 0xd7 && row == 0x00) {
				return 0x08;
			}
			else if (col == 0xdb && row == 0x01) {
				return 0x09;
			}
			else if (col == 0xdd && row == 0x02) {
				return 0x0a;
			}
			else if (col == 0xde && row == 0x03) {
				return 0x0b;
			}
			else if (col == 0xe7 && row == 0x00) {
				return 0x0c;
			}
			else if (col == 0xeb && row == 0x01) {
				return 0x0d;
			}
			else if (col == 0xed && row == 0x02) {
				return 0x0e;
			}
			else if (col == 0xee && row == 0x03) {
				return 0x0f;
			}
			else {
				return 0xff;		// returns 0xff when nothing pressed
			}
		}
	}
	return 0xff;
}