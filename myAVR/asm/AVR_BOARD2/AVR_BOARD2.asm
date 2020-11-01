.INCLUDE "M2560DEF.INC"
.ORG 00





LDI R16, 0xFF // stack initialisation
OUT SPL, R16
LDI R16, 0x21
OUT SPH, R16

LDI R16, 0xFF
OUT DDRB, R16

main_loop:
LDI R16, 0xFF
OUT PORTB, R16
LDI R16, 0xff // przekazanie 1-go parametru
PUSH R16
LDI R16, 0xff 
PUSH R16
CALL delay 
POP R16
POP R16
LDI R16, 0x00
OUT PORTB, R16
LDI R16, 0xff // przekazanie 1-go parametru
PUSH R16
LDI R16, 0x7f // przekazanie 2-go parametru
PUSH R16
CALL delay // the call-site

POP R16
POP R16
JMP main_loop

stop:
JMP stop

delay: // the callee
PUSH R16 // The saving of the working registers
PUSH R17
PUSH R26
PUSH R27
PUSH R18

IN R26, SPL
IN R27, SPH
ADIW R26, 11
LD R16, -X
LD R17, -X

outer: // The function body
CPI R16, 0x00
BREQ end_delay
DEC R16
MOV R18, R17
inner:
CPI R18, 0x00
BREQ outer
DEC R18
JMP inner

end_delay:
POP R18 // The restoring of the working registers
POP R27
POP R26
POP R17
POP R16
RET // The return from the function

// VIACallingConventions.pdf 
