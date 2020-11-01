
#include "driver.h"

/* macros */
#define DDR(x) (*(&x - 1))      /* address of data direction register of port x */
#define PIN(x) (*(&x - 2))      /* address of input register of port x          */

void init_bargraph()
{
	DDR(BARGRAPH_PORT_DIR) |= _BV(BARGRAPH_OE);
	DDR(BARGRAPH_PORT_DIR) |= _BV(BARGRAPH_DATA);
	DDR(BARGRAPH_PORT_DIR) |= _BV(BARGRAPH_CP);
	DDR(BARGRAPH_PORT_DIR) |= _BV(BARGRAPH_STR);
	
}


/*
CP OE STR D  QP0 QPn		H = HIGH voltage level;
U  L  X   X  Z   Z			L = LOW voltage level;
D  L  X   X  Z   Z			X = don’t care;
U  H  L   X  N   N			U = LOW-to-HIGH clock transition;
U  H  H   L  Z   QPn-1		D = HIGH-to-LOW clock transition;
U  H  H   H  L   QPn-1		Z = high-impedance OFF-state;
D  H  H   H  N   N     		N = no change
*/


void bargraph_write(uint8_t bit)
{
	// OE goes HIGH
	BARGRAPH_PORT |= BARGRAPH_OE;
	
	
	
	// OE goes LOW
	BARGRAPH_PORT &= BARGRAPH_OE;
	
}


void diplay(uint8_t value)
{
	
	
	
}

