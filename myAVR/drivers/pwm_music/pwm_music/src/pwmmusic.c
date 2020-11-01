/*
Microcontroller: ATmega16 or ATmega32
Clock: 8 MHz
External hardware: Piezzo buzzer/speaker connected to (OC5B) PL4

http://aquaticus.info/pwm-music

*/

#include <avr/io.h>
#include <util/delay.h>
#include "speaker.h"
#include "notes.h"	// The output file from notegen.pl script

#define BUTIN() (PINC & 0x01) == 0



int main()
{
	uint8_t state = 2;
	char buf[64] = {};
	
	char but;		 //button state
	char butl;		 //button last pass
	char butos;		 //button pressed oneshot

	DDRA = 0xff;
	DDRC = 0x00;
	DDRG = 0xff;

	//	lcd_init(LCD_DISP_ON);
	InitMusic();
	
	while(1)
	{

		PORTA = PINC;

		but = BUTIN();				  //read button
		butos = but && !butl;		  //generate oneshot
		butl = but;					  //remember last pass
		
		if(butos != 0) {
			
			PlayTakeOff();
			PlayEmergency(5);
			PlayLanding(5);
			PlayOverheating(5);
		}
		
		else
		{
			ShutUp();
		}
	}
}

