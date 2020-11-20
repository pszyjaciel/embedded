/*
 * MyUtils.h
 *
 *  Created on: Nov 16, 2020
 *      Author: arleta
 */

#ifndef MYUTILS_H_
#define MYUTILS_H_

#include <DAVE.h>

//p0.5  40040004H(address) 0x00000020(set) 0x00200000(reset)
//p0.0	40040004H(address) 0x00000001(set) 0x00010000(reset)
//p2.11 40040204H(address) 0x00000800(set) 0x08000000(reset)
//p2.10 40040204H(address) 0x00000400(set) 0x04000000(reset)

// port start end
//P0 40040000H 400400FFH
//P1 40040100H 400401FFH
//P2 40040200H 400402FFH

// only for CP-voltage divider: (0.2V na dzialke)
#define CLEAROSCIBIT0 asm("ldr r0, =0x00200000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t")
#define CLEAROSCIBIT1 asm("ldr r0, =0x00010000\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t")
#define CLEAROSCIBIT2 asm("ldr r0, =0x08000000\n\t" "ldr r1, =0x40040204\n\t" "str r0, [r1]\n\t")
#define CLEAROSCIBIT3 asm("ldr r0, =0x04000000\n\t" "ldr r1, =0x40040204\n\t" "str r0, [r1]\n\t")

#define SETOSCIBIT0 asm("ldr r0, =0x00000020\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t")
#define SETOSCIBIT1 asm("ldr r0, =0x00000001\n\t" "ldr r1, =0x40040004\n\t" "str r0, [r1]\n\t")
#define SETOSCIBIT2 asm("ldr r0, =0x00000800\n\t" "ldr r1, =0x40040204\n\t" "str r0, [r1]\n\t")
#define SETOSCIBIT3 asm("ldr r0, =0x00000400\n\t" "ldr r1, =0x40040204\n\t" "str r0, [r1]\n\t")

volatile bool czasMinou;

void TrackSignalByValue(volatile uint8_t myValue);
void myDelayMS(uint32_t milliSec);

#endif /* MYUTILS_H_ */
