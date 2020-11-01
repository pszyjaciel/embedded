
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "speaker.h"


void Timer_Init(void) {
	// 16bit
	OCR5A = 0x1D08;					// value to compare, when increases the frequency pull down
	TCCR5A |= (1 << COM5B0);		// toggle output OC5B on compare match
	TCCR5B |= (1 << WGM52);			// Mode: CTC (page 148)
	TCCR5B |= (1 << CS50);			// no prescaling
}

void Speaker_Init(void) {
	SPEAKER_OUTPUT_ENABLE;
	Timer_Init();
}



void PlaySound(uint8_t note)
{
	switch (note)
	{
		case 0:
		OCR5A += 0x0400;
		break;
		
		case 1:
		OCR5A += 0x0800;
		break;

		case 2:
		OCR5A += 0x0c00;
		break;

		case 3:
		OCR5A += 0x1000;
		break;

		case 4:
		OCR5A = note;
		break;

		case 5:
		OCR5A = note;
		break;

		case 6:
		OCR5A = note;
		break;

		case 7:
		OCR5A = note;
		break;
		
		default:
		OCR5A = note;
		
	}
}