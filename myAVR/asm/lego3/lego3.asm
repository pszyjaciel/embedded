.INCLUDE "LegoInterface.asm"
.INCLUDE "InterruptVectorTable.asm"
.INCLUDE "delay.asm"

.ORG 0x0300

.DB "a meessage on this line"

/*
lego functions:
	init_lego_interface
	lego_abs
	touch_sensor - R24 is the number of the sensor
	rotation_sensor
	light_sensor - R24 is sensor number
	motor_speed - R22 is speed, R24 is motor_no
	brake_motor
*/

// http://avr.8b.cz/pdf/skd_c_7_en.pdf

.EQU counter = 0x10

DATA:
.DB 11, 22, 33, 44, 55, 66, 77, 88, 99, 111, 122, 133, 144, 155, 166, 177

average: // output in r24
	push r16
	push r17
	push r18
	push r19	

	ldi r18, counter
	ldi r16, 0
	ldi r17, 0

next_value:
//	ld r16, X+

	lpm r19, Z+
	adc r16, r19
	brcc go_further
	inc r17

go_further:
	dec r18		// decrement the counter
	brne next_value

	lsr r16 	//podzielenie przez 2
	lsr r16 	//podzielenie przez 2
	lsr r16 	//podzielenie przez 2
	lsr r16 	//podzielenie przez 2

	lsl r17
	lsl r17
	lsl r17
	lsl r17
	
	or r16, r17
	mov r24, r16

exit:
	pop r19
	pop r18
	pop r17
	pop r16
	ret

Main:
	CALL init_lego_interface

begin:
	ldi ZH, high(2*DATA) // X is the pointer
	ldi ZL, low(2*DATA)
	ldi r16, counter

again:
	ldi r24, 0
//	call light_sensor
//	st X+, r24
	dec r16 
	brne again
	call average
	cpi r24, 0x20
	brcc begin
	
// display_value
	ldi r24, 0x3e
	out PORTA, R24

// check_touch_sensor
	ldi r24, 0
	call touch_sensor
	cpi R24, 255  //255 - not pressed
	brcc begin

/*
// booth_empty
	call light_sensor
	cpi R24, 0x80
	brcc begin
*/

// start_motor
	ldi r22, 0x80
	ldi r24, 0
	call motor_speed

wait_5sec:
	ldi r16, 50
	push R16
//	call delay
	pop R16

jmp begin






/*
begin: // stay here until no car
	ldi r24, 0
	call light_sensor
	cpi R24, 0x80
	brcc begin

*/


/*
BEGIN:
LDI R24, 0
CALL touch_sensor

// IN R24, PINF

out porta, r24

out porta, r25


JMP BEGIN
*/

/*
LDI R16, 0X00  // PORTF AS INPUT
OUT DDRF, R16

LDI R16, 0XFF
OUT DDRA, R16	// PORTA AS OUTPUT
OUT PORTA, R16	// TURN OFF ALL LED'S
*/
