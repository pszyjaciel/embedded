/*
* bcd_7segment.h
*
* Created: 4/29/2015 9:25:34 PM
*  Author: root
*/


#ifndef BCD_7SEGMENT_H_
#define BCD_7SEGMENT_H_


#define SHCP PB1
#define DS PB2
#define MR PB3
#define STCP PK3

#define A PL3
#define B PL2
#define C PL1
#define D PL0

uint8_t myTable[20];

void load_shift_register(uint8_t pattern);
void load_digit_paterns(uint8_t digit, uint8_t pattern);
void display_7_segment(float value, uint8_t no_of_decimals);
void timer0_init();
void init_7_segment();

#endif /* BCD_7SEGMENT_H_ */