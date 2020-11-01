/*
.section .text
.global _start

_start:
.THUMB
// socket(2, 1, 0)
 mov   r0, #2
 mov   r1, #1
 sub   r2, r2
 mov   r7, #200
 add   r7, #81         // r7 = 281 (socket)
 svc   #1              // r0 = resultant sockfd
 mov   r4, r0          // save sockfd in r4
*/

.syntax unified
.cpu cortex-m3
.thumb

.word 0x20000400
.word 0x080000ed
.space 0xe4

nop     @ Do Nothing
b .     @ Endless loop
