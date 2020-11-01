
.INCLUDE "M2560DEF.INC"

jmp start

//start:
// initialize the stack
ldi r16, low(RAMEND)
out spl, r16
ldi r16, high(RAMEND)
out sph, r16


ldi r16, 0xff // direction
out DDRA, r16

begin:
ldi r16, 0xfe // 0b11111110
out PORTA, r16

ldi r17, 0x10
call vastetime


ldi r16, 0x7f // 0b01111111
out PORTA, r16

ldi r17, 0x04
call vastetime

jmp begin


vastetime:
push r17
push r18
push r19

ldi r19, 0xff // 255
ldi r18, 0xff

loop:
nop
dec r19
brne loop
dec r18
brne loop
dec r17
brne loop

pop r19
pop r18
pop r17
ret


start:
// initialize the stack
ldi r16, 0xff
out spl, r16
ldi r16, 0x21
out sph, r16

ldi r16, 0xff // direction
out DDRA, r16

begin2:
ldi r16, 0x7f // 0b01111111
out PORTA, r16

ldi r18, 0x08 // bits counter

loop2:
lsl R16
out PORTA, r16
ldi r17, 0x02 // delay counter
rcall vastetime
dec r18
brne loop2

jmp begin2


