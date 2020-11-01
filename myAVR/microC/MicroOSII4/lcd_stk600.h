/*
 * lcd_stk600.h
 *
 * Created: 15-03-2014 16:38:50
 *  Author: IHA
 */ 


#ifndef LCD_STK600_H_
#define LCD_STK600_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "ab_encoder/ab-encoder.h"
#include "lcd/lcd.h"

#define LCD_STK600_GREEN_LED 4
#define LCD_STK600_RED_LED   5
#define LCD_STK600_LED_ON 1
#define LCD_STK600_LED_OFF 0

#define LCD_STK600_SW0 0
#define LCD_STK600_SW1 1
#define LCD_STK600_SW2 2
#define LCD_STK600_SW3 3

void lcd_stk600_init();
void lcd_stk600_led(uint8_t led, uint8_t state);
uint8_t lcd_stk600_sw_pressed(uint8_t key_no);
uint8_t lcd_stk600_all_sw();

#endif /* LCD_STK600_H_ */