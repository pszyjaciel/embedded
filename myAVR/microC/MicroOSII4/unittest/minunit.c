/*
* minunit.c
*
* Created: 8/19/2015 11:41:16 AM
*  Author: root
*/


#include <avr/io.h>
#include "minunit.h"
#include "../lcd_stk600.h"


// test if encoder set in zero position
static char *test_encoder() {
	uint8_t key = ab_encoder_current_position(0);
	mu_assert("Encoder not in Zero", key == 0);
	return 0;
}


// test if STK buttons are not shorted
static char *test_STK600Buttons() {
	for (uint8_t i = 0; i < 4; i++)
	{
		uint8_t key = ~PINC;
		mu_assert("STK-buttons\nare shorted!", key == 0);
	}
	return 0;
}


// test if LCD buttons are not shorted
static char *test_LCDButtons() {
	for (uint8_t i = 0; i < 4; i++)
	{
		uint8_t key = lcd_stk600_sw_pressed(i);
		mu_assert("LCD-buttons\nare shorted!", key == 0);
	}
	return 0;
}


static char *all_tests() {
	mu_run_test(test_STK600Buttons);
	mu_run_test(test_LCDButtons);
	mu_run_test(test_encoder);
	return 0;
}


// the main routine for the unit test called from app.c (after initialization)
int runUnitTest() {
	lcd_gotoxy(0, 0);
	char *result = all_tests();		// returns an error-message in case of error, or 0 otherwise
	
	if (result != 0) {
		lcd_puts(result);
		lcd_stk600_led(LCD_STK600_RED_LED, LCD_STK600_LED_ON);
		lcd_stk600_led(LCD_STK600_GREEN_LED, LCD_STK600_LED_OFF);
		return 0;
	}
	
	else {
		lcd_puts("ALL TESTS PASSED");
		lcd_stk600_led(LCD_STK600_GREEN_LED, LCD_STK600_LED_ON);
		lcd_stk600_led(LCD_STK600_RED_LED, LCD_STK600_LED_OFF);
		return 1;
	}
	return 0;
}

