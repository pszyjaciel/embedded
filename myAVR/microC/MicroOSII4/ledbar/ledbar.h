/************************************************************
 *            File: ledbar.h                                *
 * Purpose: Declarations on hardware configuration for      *
 *          LED Bar Graph Display                           *
 * Date:    10-04-2014                                      *
 * Author:  Erland Larsen, VIA University College           *
 ************************************************************/

//#ifdef(LEDBAR_SRC)
	/* Define the Port connected to LED Bar Graph Display */
#define LEDBAR_PORT	PORTF
#define LEDBAR_DDR	DDRF

/* Signals */
#define LEDBAR_D	0
#define LEDBAR_CP	1
#define LEDBAR_STR	2
#define LEDBAR_EO	3

//#else
extern void clr_bar(void);
extern void put_bar( char level );
//#endif
