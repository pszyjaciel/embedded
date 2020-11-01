
#define F_CPU 14745600

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "lcd.h"


int main(void)
{

	lcd_init(LCD_DISP_ON_CURSOR);
	
    while(1)
    {
		_delay_ms(100);
		lcd_gotoxy(0, 0);
		lcd_putc('A');
		
		_delay_ms(100);
		lcd_gotoxy(0, 1);
		lcd_putc('B');

		_delay_ms(100);
		lcd_clrscr();


		
        //TODO:: Please write your application code 
    }
}