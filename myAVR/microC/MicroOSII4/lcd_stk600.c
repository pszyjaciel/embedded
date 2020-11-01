/*
* $safeprojectname$.c
*
* Created: 15-03-2014 16:34:36
*  Author: IHA
*/

#include "lcd_stk600.h"

void lcd_stk600_init() {
	// ab_encoder
	// Enable Pull-up on INT6 & INT7
	PORTE |= _BV(PE6) | _BV(PE7);
	
	USART_putstring("\nbefore: lcd_stk600.c lcd_stk600_init()\r\n");
	ab_encoder_init();
	USART_putstring("\nafter: lcd_stk600.c lcd_stk600_init()\r\n");
	
	// LCD
	USART_putstring("\nbefore: lcd_stk600.c lcd_init()\r\n");
	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
	USART_putstring("\nafter: lcd_stk600.c lcd_init()\r\n");
	
	// Led's
	// Set port pins to output
	DDRE |= _BV(DDE4) | _BV(DDE5);
	
	// Switches 0 - 3
	// Enable Pull-up on PE0-PE3
	PORTE |= _BV(PE0) | _BV(PE1) | _BV(PE2) | _BV(PE3);
}

void lcd_stk600_led(uint8_t led, uint8_t state) {
	if (led >= LCD_STK600_GREEN_LED && led <=LCD_STK600_RED_LED) {
		if (state == LCD_STK600_LED_ON) {
			PORTE |= _BV(led);
			}else {
			PORTE &= ~_BV(led);
		}
	}
}

uint8_t lcd_stk600_sw_pressed(uint8_t key_no) {
	return (PINE & _BV(key_no) ? 0 : 1);
	// condition ? valueIfTrue : valueIfFalse
}

uint8_t lcd_stk600_all_sw() {
	return (~PINE) & 0x0F;
}