/*
functions:
	init_lego_interface
	lego_abs
	touch_sensor
	rotation_sensor
	light_sensor - R24 is sensor number
	motor_speed - R22 is speed, R24 is motor_no
	brake_motor
*/

.INCLUDE "M2560DEF.INC"

.EQU __SREG__ = 0x3f
.EQU __SP_H__ = 0x3e
.EQU __SP_L__ = 0x3d
.EQU __CCP__  = 0x34
#define __tmp_reg__ r0
#define __zero_reg__ r1
	
.EQU sensor_channel = 0x300    /* 1 byte of data */
.EQU motor_braked = 0x304      /* 8 bytes of data */
.EQU sensor_result = 0x30C     /* 16 bytes of data */

#define lo8(x) (x & 0xff)
#define hi8(x) (x >> 8)

.ORG 0x400

lego_abs:
	push r29
	push r28
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	tst r25
	brge L2
	ldd r24,Y+1
	ldd r25,Y+2
	clr r18
	clr r19
	sub r18,r24
	sbc r19,r25
	std Y+4,r19
	std Y+3,r18
	rjmp L3
L2:
	ldd r24,Y+1
	ldd r25,Y+2
	std Y+4,r25
	std Y+3,r24
L3:
	ldd r24,Y+3
	ldd r25,Y+4
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret

init_lego_interface:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(124)
	ldi r27,hi8(124)
	ldi r30,lo8(124)
	ldi r31,hi8(124)
	ld r24,Z
	ori r24,lo8(64)
	st X,r24
	ldi r26,lo8(122)
	ldi r27,hi8(122)
	ldi r30,lo8(122)
	ldi r31,hi8(122)
	ld r24,Z
	ori r24,lo8(-128)
	st X,r24
	ldi r26,lo8(122)
	ldi r27,hi8(122)
	ldi r30,lo8(122)
	ldi r31,hi8(122)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(122)
	ldi r27,hi8(122)
	ldi r30,lo8(122)
	ldi r31,hi8(122)
	ld r24,Z
	ori r24,lo8(6)
	st X,r24
	ldi r30,lo8(126)
	ldi r31,hi8(126)
	ldi r24,lo8(-1)
	st Z,r24
	ldi r26,lo8(145)
	ldi r27,hi8(145)
	ldi r30,lo8(145)
	ldi r31,hi8(145)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r30,lo8(152)
	ldi r31,hi8(152)
	ldi r24,lo8(15624)
	ldi r25,hi8(15624)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(113)
	ldi r27,hi8(113)
	ldi r30,lo8(113)
	ldi r31,hi8(113)
	ld r24,Z
	ori r24,lo8(2)
	st X,r24
	ldi r30,lo8(148)
	ldi r31,hi8(148)
	std Z+1,__zero_reg__
	st Z,__zero_reg__
	ldi r26,lo8(145)
	ldi r27,hi8(145)
	ldi r30,lo8(145)
	ldi r31,hi8(145)
	ld r24,Z
	ori r24,lo8(3)
	st X,r24
	ldi r26,lo8(36)
	ldi r27,hi8(36)
	ldi r30,lo8(36)
	ldi r31,hi8(36)
	ld r24,Z
	ori r24,lo8(-32)
	st X,r24
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	andi r24,lo8(31)
	st X,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	ldi r26,lo8(129)
	ldi r27,hi8(129)
	ldi r30,lo8(129)
	ldi r31,hi8(129)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(-88)
	st X,r24
	ldi r18,lo8(136)
	ldi r19,hi8(136)
	ldi r26,lo8(138)
	ldi r27,hi8(138)
	ldi r30,lo8(140)
	ldi r31,hi8(140)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	ld r24,X+
	ld r25,X
	movw r30,r18
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(129)
	ldi r27,hi8(129)
	ldi r30,lo8(129)
	ldi r31,hi8(129)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	ldi r26,lo8(257)
	ldi r27,hi8(257)
	ldi r30,lo8(257)
	ldi r31,hi8(257)
	ld r24,Z
	ori r24,lo8(56)
	st X,r24
	ldi r26,lo8(258)
	ldi r27,hi8(258)
	ldi r30,lo8(258)
	ldi r31,hi8(258)
	ld r24,Z
	andi r24,lo8(-57)
	st X,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	ldi r26,lo8(161)
	ldi r27,hi8(161)
	ldi r30,lo8(161)
	ldi r31,hi8(161)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(-88)
	st X,r24
	ldi r18,lo8(168)
	ldi r19,hi8(168)
	ldi r26,lo8(170)
	ldi r27,hi8(170)
	ldi r30,lo8(172)
	ldi r31,hi8(172)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	ld r24,X+
	ld r25,X
	movw r30,r18
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(161)
	ldi r27,hi8(161)
	ldi r30,lo8(161)
	ldi r31,hi8(161)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	ldi r26,lo8(266)
	ldi r27,hi8(266)
	ldi r30,lo8(266)
	ldi r31,hi8(266)
	ld r24,Z
	ori r24,lo8(24)
	st X,r24
	ldi r26,lo8(267)
	ldi r27,hi8(267)
	ldi r30,lo8(267)
	ldi r31,hi8(267)
	ld r24,Z
	andi r24,lo8(-25)
	st X,r24
	ldi r26,lo8(288)
	ldi r27,hi8(288)
	ldi r30,lo8(288)
	ldi r31,hi8(288)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	ldi r26,lo8(289)
	ldi r27,hi8(289)
	ldi r30,lo8(289)
	ldi r31,hi8(289)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(288)
	ldi r27,hi8(288)
	ldi r30,lo8(288)
	ldi r31,hi8(288)
	ld r24,Z
	ori r24,lo8(-96)
	st X,r24
	ldi r26,lo8(296)
	ldi r27,hi8(296)
	ldi r30,lo8(298)
	ldi r31,hi8(298)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	ldi r26,lo8(289)
	ldi r27,hi8(289)
	ldi r30,lo8(289)
	ldi r31,hi8(289)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret

touch_sensor:
	push r29
	push r28
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+1,r24
	ldd r24,Y+1
	cpi r24,lo8(8)
	brsh L8
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	lsl r24
	rol r25
	movw r30,r24
	subi r30,lo8(-(sensor_result))
	sbci r31,hi8(-(sensor_result))
	ld r24,Z
	ldd r25,Z+1
	std Y+3,r25
	std Y+2,r24
	rjmp L9
L8:
	ldi r24,lo8(-1)
	ldi r25,hi8(-1)
	std Y+3,r25
	std Y+2,r24
L9:
	ldd r24,Y+2 // RESULT1
	ldd r25,Y+3	// RESULT2
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret

rotation_sensor:
	push r29
	push r28
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+1,r24
	ldd r24,Y+1
	cpi r24,lo8(8)
	brsh L12
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	lsl r24
	rol r25
	movw r30,r24
	subi r30,lo8(-(sensor_result))
	sbci r31,hi8(-(sensor_result))
	ld r24,Z
	ldd r25,Z+1
	std Y+3,r25
	std Y+2,r24
	rjmp L13
L12:
	ldi r24,lo8(-1)
	ldi r25,hi8(-1)
	std Y+3,r25
	std Y+2,r24
L13:
	ldd r24,Y+2
	ldd r25,Y+3
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret

light_sensor:
	push r29
	push r28
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+1,r24
	ldd r24,Y+1
	cpi r24,lo8(8)
	brsh L16
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	lsl r24
	rol r25
	movw r30,r24
	subi r30,lo8(-(sensor_result))
	sbci r31,hi8(-(sensor_result))
	ld r24,Z
	ldd r25,Z+1
	std Y+3,r25
	std Y+2,r24
	rjmp L17
L16:
	ldi r24,lo8(-1)
	ldi r25,hi8(-1)
	std Y+3,r25
	std Y+2,r24
L17:
	ldd r24,Y+2
	ldd r25,Y+3
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret

; Seems like r22 is speed
; Seems like r24 is motor_no
motor_speed:
	push r29
	push r28
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 5 */
	std Y+2,r24
	std Y+3,r22
	ldd r24,Y+3
	cpi r24,lo8(-127)
	brne LR1
	rjmp L38
LR1:
	ldd r24,Y+3
	cpi r24,lo8(126)
	brne LR2
	rjmp L38
LR2:
	ldd r24,Y+3
	clr r25
	sbrc r24,7
	com r25
	call lego_abs
	lsl r24
	com r24
	std Y+1,r24
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	movw r30,r24
	subi r30,lo8(-(motor_braked))
	sbci r31,hi8(-(motor_braked))
	ld r24,Z
	tst r24
	breq L21
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	movw r30,r24
	subi r30,lo8(-(motor_braked))
	sbci r31,hi8(-(motor_braked))
	st Z,__zero_reg__
L21:
	ldd r24,Y+2
	mov r18,r24
	ldi r19,lo8(0)
	std Y+5,r19
	std Y+4,r18
	ldd r24,Y+4
	ldd r25,Y+5
	cpi r24,1
	cpc r25,__zero_reg__
	brne LR3
	rjmp L23
LR3:
	ldd r18,Y+4
	ldd r19,Y+5
	cpi r18,2
	cpc r19,__zero_reg__
	brge L26
	ldd r24,Y+4
	ldd r25,Y+5
	sbiw r24,0
	breq L22
	rjmp L38
L26:
	ldd r18,Y+4
	ldd r19,Y+5
	cpi r18,2
	cpc r19,__zero_reg__
	brne LR4
	rjmp L24
LR4:
	ldd r24,Y+4
	ldd r25,Y+5
	cpi r24,3
	cpc r25,__zero_reg__
	brne LR5
	rjmp L25
LR5:
	rjmp L38
L22:
	ldd r24,Y+3
	cp __zero_reg__,r24
	brge L27
	ldi r30,lo8(136)
	ldi r31,hi8(136)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(138)
	ldi r31,hi8(138)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(-96)
	st X,r24
	rjmp L38
L27:
	ldd r24,Y+3
	tst r24
	brne L29
	ldi r26,lo8(136)
	ldi r27,hi8(136)
	ldi r30,lo8(138)
	ldi r31,hi8(138)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(-96)
	st X,r24
	rjmp L38
L29:
	ldi r30,lo8(138)
	ldi r31,hi8(138)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(136)
	ldi r31,hi8(136)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(-96)
	st X,r24
	rjmp L38
L23:
	ldd r24,Y+3
	cp __zero_reg__,r24
	brge L30
	ldi r30,lo8(140)
	ldi r31,hi8(140)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(168)
	ldi r31,hi8(168)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(-128)
	st X,r24
	rjmp L38
L30:
	ldd r24,Y+3
	tst r24
	brne L32
	ldi r26,lo8(140)
	ldi r27,hi8(140)
	ldi r30,lo8(168)
	ldi r31,hi8(168)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(-128)
	st X,r24
	rjmp L38
L32:
	ldi r30,lo8(168)
	ldi r31,hi8(168)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(140)
	ldi r31,hi8(140)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(-128)
	st X,r24
	rjmp L38
L24:
	ldd r24,Y+3
	cp __zero_reg__,r24
	brge L33
	ldi r30,lo8(170)
	ldi r31,hi8(170)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(172)
	ldi r31,hi8(172)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(40)
	st X,r24
	rjmp L38
L33:
	ldd r24,Y+3
	tst r24
	brne L35
	ldi r26,lo8(170)
	ldi r27,hi8(170)
	ldi r30,lo8(172)
	ldi r31,hi8(172)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(40)
	st X,r24
	rjmp L38
L35:
	ldi r30,lo8(172)
	ldi r31,hi8(172)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(170)
	ldi r31,hi8(170)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	ori r24,lo8(40)
	st X,r24
	rjmp L38
L25:
	ldd r24,Y+3
	cp __zero_reg__,r24
	brge L36
	ldi r30,lo8(296)
	ldi r31,hi8(296)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(298)
	ldi r31,hi8(298)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(288)
	ldi r27,hi8(288)
	ldi r30,lo8(288)
	ldi r31,hi8(288)
	ld r24,Z
	ori r24,lo8(-120)
	st X,r24
	rjmp L38
L36:
	ldd r24,Y+3
	tst r24
	brne L37
	ldi r26,lo8(296)
	ldi r27,hi8(296)
	ldi r30,lo8(298)
	ldi r31,hi8(298)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	ldi r26,lo8(288)
	ldi r27,hi8(288)
	ldi r30,lo8(288)
	ldi r31,hi8(288)
	ld r24,Z
	ori r24,lo8(-96)
	st X,r24
	rjmp L38
L37:
	ldi r30,lo8(298)
	ldi r31,hi8(298)
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(296)
	ldi r31,hi8(296)
	ldi r24,lo8(255)
	ldi r25,hi8(255)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(288)
	ldi r27,hi8(288)
	ldi r30,lo8(288)
	ldi r31,hi8(288)
	ld r24,Z
	ori r24,lo8(-120)
	st X,r24
L38:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret

brake_motor:
	push r29
	push r28
	push __tmp_reg__
	push __tmp_reg__
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+1,r24
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	movw r30,r24
	subi r30,lo8(-(motor_braked))
	sbci r31,hi8(-(motor_braked))
	ld r24,Z
	tst r24
	breq LR6
	rjmp L46
LR6:
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	movw r30,r24
	subi r30,lo8(-(motor_braked))
	sbci r31,hi8(-(motor_braked))
	ldi r24,lo8(1)
	st Z,r24
	ldd r24,Y+1
	mov r18,r24
	ldi r19,lo8(0)
	std Y+3,r19
	std Y+2,r18
	ldd r24,Y+2
	ldd r25,Y+3
	cpi r24,1
	cpc r25,__zero_reg__
	breq L42
	ldd r18,Y+2
	ldd r19,Y+3
	cpi r18,2
	cpc r19,__zero_reg__
	brge L45
	ldd r24,Y+2
	ldd r25,Y+3
	sbiw r24,0
	breq L41
	rjmp L46
L45:
	ldd r18,Y+2
	ldd r19,Y+3
	cpi r18,2
	cpc r19,__zero_reg__
	breq L43
	ldd r24,Y+2
	ldd r25,Y+3
	cpi r24,3
	cpc r25,__zero_reg__
	breq L44
	rjmp L46
L41:
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	andi r24,lo8(95)
	st X,r24
	rjmp L46
L42:
	ldi r26,lo8(128)
	ldi r27,hi8(128)
	ldi r30,lo8(128)
	ldi r31,hi8(128)
	ld r24,Z
	andi r24,lo8(-9)
	st X,r24
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	andi r24,lo8(127)
	st X,r24
	rjmp L46
L43:
	ldi r26,lo8(160)
	ldi r27,hi8(160)
	ldi r30,lo8(160)
	ldi r31,hi8(160)
	ld r24,Z
	andi r24,lo8(-41)
	st X,r24
	rjmp L46
L44:
	ldi r26,lo8(288)
	ldi r27,hi8(288)
	ldi r30,lo8(288)
	ldi r31,hi8(288)
	ld r24,Z
	andi r24,lo8(95)
	st X,r24
L46:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret

__vector_32:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	lds r0,91
	push r0
	clr __zero_reg__
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	ldi r30,lo8(48)
	ldi r31,hi8(48)
	st Z,__zero_reg__
	ldi r30,lo8(49)
	ldi r31,hi8(49)
	st Z,__zero_reg__
	ldi r26,lo8(124)
	ldi r27,hi8(124)
	ldi r30,lo8(124)
	ldi r31,hi8(124)
	ld r24,Z
	mov r25,r24
	andi r25,lo8(-8)
	lds r24,sensor_channel
	add r24,r25
	st X,r24
	ldi r26,lo8(122)
	ldi r27,hi8(122)
	ldi r30,lo8(122)
	ldi r31,hi8(122)
	ld r24,Z
	ori r24,lo8(64)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r0
	sts 91,r0
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti

__vector_29:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	lds r0,91
	push r0
	clr __zero_reg__
	push r18
	push r19
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	lds r24,sensor_channel
	mov r24,r24
	ldi r25,lo8(0)
	ldi r30,lo8(120)
	ldi r31,hi8(120)
	ld r18,Z
	ldd r19,Z+1
	lsl r24
	rol r25
	movw r30,r24
	subi r30,lo8(-(sensor_result))
	sbci r31,hi8(-(sensor_result))
	std Z+1,r19
	st Z,r18
	lds r24,sensor_channel
	cpi r24,lo8(7)
	brsh L50
	ldi r26,lo8(124)
	ldi r27,hi8(124)
	ldi r30,lo8(124)
	ldi r31,hi8(124)
	ld r24,Z
	mov r25,r24
	andi r25,lo8(-8)
	lds r24,sensor_channel
	subi r24,lo8(-(1))
	sts sensor_channel,r24
	lds r24,sensor_channel
	add r24,r25
	st X,r24
	ldi r26,lo8(122)
	ldi r27,hi8(122)
	ldi r30,lo8(122)
	ldi r31,hi8(122)
	ld r24,Z
	ori r24,lo8(64)
	st X,r24
	rjmp L52
L50:
	ldi r30,lo8(48)
	ldi r31,hi8(48)
	ldi r24,lo8(-1)
	st Z,r24
	ldi r30,lo8(49)
	ldi r31,hi8(49)
	ldi r24,lo8(-1)
	st Z,r24
	sts sensor_channel,__zero_reg__
L52:
/* epilogue start */
	pop r28
	pop r29
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r19
	pop r18
	pop r0
	sts 91,r0
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
