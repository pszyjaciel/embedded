
/*
H-bridge:
PORTG:
I6: A-IA: PG4
I7: A-IB: PG5

I7 I6 O4 O1
H  L  H  L
L  H  L  H
H  H  L  L		(brake)
L  L  Open Open (standby)
--------------

LCD connected to PORTD

Speaker:
braun: +5V
black: GND
white: PG0 (signal)
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

#define BUTIN() (PINC & 0x01) == 0
#define ENGINE_PORT PORTG

char but;		 //button state
char butl;		 //button last pass
char butos;		 //button pressed oneshot


// speed must be a byte between 0-255
void runLeft(uint8_t speed)
{
	ENGINE_PORT |= (1 << PG4) & ~(1 << PG3) & ~(1 << PG2);
	OCR0B = ~speed;
}

// speed must be a byte between 0-255
void runRight(uint8_t speed)
{
	ENGINE_PORT &= ~(1 << PG4) & ~(1 << PG3) & ~(1 << PG2);
	OCR0B = speed;
}


void Timer0_Init(void) {
	OCR0B = 0x01;								// Output Compare Register A (stores the compare value)
	TCCR0A |= (1 << COM0B1);					// None-inverted mode (HIGH at bottom, LOW on Match)
	TCCR0A |= (1 << WGM01) | (1 << WGM00);      // Fast PWM
	TCCR0B |= (1 << CS01) | (1 << CS00);        // mnoznik
}

int main (void)
{
	uint8_t state = 2;
	char buf[64] = {};

	DDRA = 0xff;
	DDRC = 0x00;
	DDRG = 0xff;

	lcd_init(LCD_DISP_ON);
	Timer0_Init();
	
	while(1)
	{

		PORTA = PINC;
		// http://electronics.stackexchange.com/questions/58348/avr-button-interfacing
		but = BUTIN();				  //read button
		butos = but && !butl;		  //generate oneshot
		butl = but;					  //remember last pass
		
		if(butos) {
			state++;
			if(state > 2) state = 0;
		}
		
		switch(state) {
			case 0:
			runLeft(0x40);
			break;
			
			case 1:
			runRight(0x40);
			ENGINE_PORT |= (1 << PG0);  // sound on
			_delay_ms(20);
			ENGINE_PORT &= ~(1 << PG0);  // sound off
			
			break;
			
			case 2:
			OCR0B = 0xff;
			ENGINE_PORT |= (1 << PG4);		//motor stop
			break;
		}
		
		lcd_gotoxy(0, 0);
		lcd_puts("OCR0B: ");
		itoa(OCR0B, buf, 16);
		lcd_puts(buf);
		lcd_putc(' ');
		

		lcd_gotoxy(0, 1);
		lcd_puts("state: ");
		itoa(state, buf, 16);
		lcd_puts(buf);
		lcd_putc(' ');
		
	}
}
