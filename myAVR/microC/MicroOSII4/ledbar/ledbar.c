/************************************************************
 *            File: ledbar.c                                *
 * Purpose: LED Bar Graph Display                           *
 * Init:    LEDBAR_DDR must be initialized in application   *
 *                                                          *
 * Date:    10-04-2014                                      *
 * Author:  Erland Larsen, VIA University College           *
 ************************************************************/
#define LEDBAR_SRC

#include <avr/io.h>
#include "ledbar.h"

void clr_bar(void)
{
	char i;

	/* DDR set here for convenience */
	LEDBAR_DDR |= (1<<LEDBAR_EO) | (1<<LEDBAR_STR) | (1<<LEDBAR_CP) | (1<<LEDBAR_D);

	LEDBAR_PORT |= (1<<LEDBAR_EO) | (1<<LEDBAR_STR);
	LEDBAR_PORT &= ~(1<<LEDBAR_CP);
	LEDBAR_PORT &= ~(1<<LEDBAR_D);
	for( i=0; i<12; i++ )
	{
		LEDBAR_PORT |= (1<<LEDBAR_CP);
		LEDBAR_PORT &= ~(1<<LEDBAR_CP);
	}
}

void put_bar( char level )
{
	char i;
	clr_bar();

	LEDBAR_PORT |= (1<<LEDBAR_EO) | (1<<LEDBAR_STR) | (1<<LEDBAR_D);
	LEDBAR_PORT |= (1<<LEDBAR_D);
	for( i=0; i<level; i++ )
	{
		LEDBAR_PORT |= (1<<LEDBAR_CP);
		LEDBAR_PORT &= ~(1<<LEDBAR_CP);
	}
}
