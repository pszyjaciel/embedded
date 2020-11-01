.INCLUDE "M2560DEF.INC"
.ORG 0X0100

MyTable:
.DW 0x1234,0x2345,0x3456,0x4568,0x5678 ; The table values, word wise
.DW 0x6789,0x789A,0x89AB,0x9ABC,0xABCD ; organized

Read5:
	LDI ZH,HIGH(MyTable*2) ; address of table to pointer Z
	LDI ZL,LOW(MyTable*2) ; multiplied by 2 for bytewise access
	ADIW ZL,10 		; Point to fifth value in table
	LPM 			; Read least significant byte from program memory
	MOV R24,R0 		; Copy LSB to 16-bit register
	ADIW ZL,1 		; Point to MSB in program memory
	LPM 			; Read MSB of table value into R0
	MOV R25,R0 		; Copy MSB to 16-bit register
