
#include <inttypes.h>
#include <avr/io.h>

#define BARGRAPH_PORT			PORTF
#define BARGRAPH_PORT_DIR		DDRF

#define BARGRAPH_OE				PF3
#define BARGRAPH_DATA			PF4
#define BARGRAPH_CP				PF5
#define BARGRAPH_STR			PF6

void init_bargraph();
void bargraph_write(uint8_t bit);
void diplay(uint8_t value);


