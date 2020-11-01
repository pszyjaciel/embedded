
.INCLUDE "m644Pdef.inc"
.ORG 0x0000
.DB 0x01, 0x02, 0x03, 0x04, 0x05, 0x06
.DB 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c


ldi xl, 0000
jmp start


// R26..R31 = X, Y, Z
delay:
push r16
push r17
push r18
push r19
push YH
push YL

ldd r17, Y+0 // 1. parametr petli
dec YL
ldd r18, Y+0 // 2. parametr
dec YL
ldd r19, Y+0 // 3. parametr

loop:
nop
nop
nop
nop
nop
dec r17
brne loop
dec r18
brne loop
dec r19
brne loop

pop YL
pop YH
pop r19
pop r18
pop r17
pop r16

ret


start:
LDI	R16, low(RAMEND)
OUT	SPL, R16
mov YL, r16 // ustawienie rejestru Y

LDI	R16, high(RAMEND)
OUT	SPH, R16
mov YH, r16

ldi r16, 0xff
out DDRB, r16

ldi r16, 0x10
ldi r17, 0x80 // R17-R19 opoznienie
ldi r18, 0x80
ldi r19, 0x10

clc
ldi r16, 0x01
out PORTB, r16

begin2:
out PORTB, r16
ror r16
push r17 	// 1. parametr
//dec r18
push r18	// 2. parametr
dec r19
brne nie_zero
ldi r19,0x10
nie_zero:
push r19	// 3. parametr
rcall delay
pop r19
pop r18
pop r17

jmp begin2
