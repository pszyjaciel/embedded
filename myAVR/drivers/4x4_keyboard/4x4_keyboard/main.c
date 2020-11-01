
// u:\!Desktop\ethernut\avrstudio\4x4_keyboard\4x4_keyboard\4x4_keyboard.c
// U:\ICT\6th_semester\hwpi1\projects\4x4_keyboard\4x4_keyboard\main.c

#include <avr/io.h>
#include "myUart.h"
#include "myUtil.h"
#include <util/delay.h>
#include "keyboard.h"


int main(void)
{
	uint8_t myKey;
	
	USART_init();
	init_keyboard();
	
	DDRH = 0xff;		// LEDs
	
	while(1)
	{
		_delay_ms(200);
		
		myKey = getKey();
		if (myKey != 0xff)
		{
			print_hexByte(myKey);
			PORTH = myKey;
		}
	}
}