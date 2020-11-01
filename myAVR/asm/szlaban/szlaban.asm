// mpc17529ev
// http://www.mlab.cz/Modules/H_Bridge/MPC17529HB01A/DOC/HTML/MPC17529HB01A.cs.html


.INCLUDE "LegoInterface.asm"
.INCLUDE "InterruptVectorTable.asm"
.INCLUDE "delay.asm"

.ORG 0x0100

/*
- the light sensor (green) connected on S1 and PORTF
- the touch sensor (blue) connected on S0 and PORTF
- the motor connected on Motor1 and PORTB (orange)
- LEDs connected on PORTA


lego functions:
	init_lego_interface
	lego_abs
	touch_sensor - R24 is the number of the sensor
	rotation_sensor
	light_sensor - R24 is sensor number
	motor_speed - R22 is speed, R24 is motor_no
	brake_motor
*/

Main:
	LDI R16, 0xFF		// Setup stack
	OUT SPL, R16
	LDI R16, 0x21
	OUT SPH, R16

	LDI R16, 0xFF		// PORTA as output
	OUT DDRA, R16

 	SUB R1, R1
	CALL init_lego_interface

	SEI  				// enable interrupts
	
	LDI R16, 25			// a litle break after reset
	PUSH R16
	CALL DELAY
	POP R16

lwait: // wait for light
	LDI R24, 0X00
	COM R24
	OUT PORTA, R24		// turn off the LED's

	LDI R24, 1
	CALL LIGHT_SENSOR
	COM R24				// reverse bits in R24
//	ANDI R24, 0XC0
	ANDI R24, 0X30
	BREQ LWAIT			// jump when no reflection

	LDI R24, 100		// display told value
	COM R24
	OUT PORTA, R24		 

BWAIT:	// wait for button
	LDI R20, 0
	LDI R24, 0
	CALL TOUCH_SENSOR	// returns 0xff when not pressed
	INC R24
	ADD R20, R24
	CALL TOUCH_SENSOR
	INC R24
	ADD R20, R24
	BREQ BWAIT 			// jump when not pressed

// display 'go!'
	LDI R24, 0X81		// display told value
	COM R24
	OUT PORTA, R24	

MOTOR:
	LDI R22, 50			// start the motor
	LDI R24, 0	
	CALL MOTOR_SPEED

	LDI R16, 14
	PUSH R16
	CALL DELAY
	POP R16

	LDI R24, 0			// stop it
	CALL BRAKE_MOTOR
	
	LDI R16, 0XFF		// long break
	PUSH R16
	CALL DELAY
	POP R16
	
	LDI R16, 0X40		// long break
	PUSH R16
	CALL DELAY
	POP R16

	LDI R22, -40		// rotate in other direction
	LDI R24, 0	
	CALL MOTOR_SPEED

	LDI R16, 16
	PUSH R16
	CALL DELAY
	POP R16

	LDI R24, 0			// stop the the motor
	CALL BRAKE_MOTOR

	JMP LWAIT
