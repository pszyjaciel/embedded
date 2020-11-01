
#include <util/delay.h>
#include "speaker.h"
#include "notes.h"

int duration;
int note;
uint16_t delay;

const int furelise[] =
{
	e4, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3,8, p, 8,
	c3, 8, e3, 8, a3, 8,  b3, 4, p, 8, e3, 8, g3x, 8, b3, 8, c4, 4, p, 8, e3, 8,
	e3, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3, 8, p, 8, c3, 8,
	e3, 8, a3, 8, b3, 4, p, 8, e3, 8, c4, 8, b3, 8, a3, 4,
	MUSIC_END
};

void ShutUp()
{
	OCR5B = 0;
}

void PlayNote(int note, int duration, uint32_t delay)
{
	int i;
	//		uint16_t delay = tempo * 1000;

	if( p == note )
	{
		//pause, do not generate any sound
		OCR5B = 0;

	}
	else
	{
		//not a pause, generate tone
		OCR5B = DEFAULT_VOLUME;

		//set frequency
		ICR5H = (note >> 8);
		ICR5L = note;

	}

	//wait duration
	for(i = 0; i < 32-duration; i++)
	{
		_delay_loop_2(delay);
	}
	
}

/** const int* pMusicNotes - Pointer to table containing music data */
/** uint8_t tempo - paying tempo from 0 to 100. Higher value = slower playback */
void PlayMusic(const int* pMusicNotes, uint8_t tempo)
{
	delay = tempo * 1000;

	while( *pMusicNotes != MUSIC_END )
	{
		note = *pMusicNotes;
		pMusicNotes++;

		duration = *pMusicNotes;
		pMusicNotes++;
		
		PlayNote(note, duration, delay);
	}
	
	//turn off any sound
	OCR5B = 0;
}


void InitMusic()
{
	//	DDRL |= _BV(DDL4);
	SPEAKER_OUTPUT_ENABLE;	// //OC5B as output

	// timer1 configuration (for PWM)
	TCCR5A |= _BV(COM5B1);  // Clear OC1A/OC1B on compare match
	
	TCCR5B |= _BV(WGM53) 	//mode 8, PWM, Phase and Frequency Correct (TOP value is ICR1)
	|_BV(CS51); 			//prescaler(8)
}


void PlayEmergency(uint8_t count)
{
	do {
		// emergency sound tuuu..tuu..tuuu (low sound, fast)
		PlayNote(C4, 2, 10000);
		PlayNote(p, 2, 10000);
		count--;
	}
	while (count > 0);
}

void PlayLanding(uint8_t count)
{
	do {
		// landing-sound (tu-tu   ............ tu-tu ..........)
		PlayNote(B4, 2, 8000);
		PlayNote(p, 2, 1000);
		PlayNote(B4, 2, 8000);
		PlayNote(p, 2, 1000);
		
		PlayNote(p, 2, 250000);
		count--;
	}
	while (count > 0);
}

void PlayOverheating(uint8_t count)
{
	do {
		// high-temperature (tiii... tiii... tiii, high frequency)
		PlayNote(B6, 2, 100000);
		PlayNote(p, 2, 10000);

		count--;
	}
	while (count > 0);
}


void PlayTakeOff()
{
	PlayMusic( furelise, 20 );
}

