/** @file rc-servo.c
@brief Triple RC-Servo driver.
@author Ib Havn
@section Description
This module is responsible for individual controlling up to three different RC-Servo motors.
@target ATMEGA1280/2560.

@revision Erland Larsen, 14-May-2014. Timer changed from 3 to 4 and port from E to H.
@note Uses TIMER4 and port pin PH3-PH5.
@note Expects F_CPU = 10 MHz!

@defgroup rc-servo RC-Servo Driver
@{
	The implementation use TIMER4 and port pins PH3-PH5.
	
	@defgroup rc-servo_private Private functions
	@brief Implementation details.
	
	@defgroup rc-servo_public Public functions
	@brief To be used from the application
@}
*/ 

#if !defined(F_CPU) || (F_CPU != 10000000L)
#error F_CPU must be defined and set to 10000000L
#endif

/* ################################################## Standard includes ################################################# */
#include <avr/io.h>

/* ################################################### Project includes ################################################# */

#include "rc-servo.h"

/* ################################################### Global Variables ################################################# */
 //!< Brief description of variable

/* ################################################### Module Variables ################################################# */


/* ################################################# Function prototypes ################################################# */


/* ======================================================================================================================= */
/**
 * @brief	Initialize the rc-servo driver.
 * @note	Should only be called once during initialisation of the application.
 *
 * @section Description
 * Setup timer 4 to Fast PWM with period 20 ms and OC4A, OC4B and OC4C as outputs
 * All three PWM outputs starts at 1.5 ms pulse width and 20 ms period time.
 */
void init_rc_servo()
{
	USART_putstring("\nbefore: rc-servoc.c init_rc_servo()\r\n");
	// Set PH3-PH5 to output
	DDRH  |= _BV(DDH3) | _BV(DDH4) | _BV(DDH5);
	
	// Set timer mode = FAST PWM, TOP: ICR4 (mode = 14)
	TCCR4A |= _BV(WGM41);
	TCCR4B |= _BV(WGM43) | _BV(WGM42);
	
	// Set OC4x pins to clear on compare match and set on BOTTOM
	TCCR4A |= _BV(COM4A1) | _BV(COM4B1) | _BV(COM4C1);
	
	// Set TOP (ICR4) to 20 ms @F_CPU=10 MHz
	ICR4 = 24999;
	
	// Set all servo's in mid position.
	rc_servo(0,0);
	rc_servo(1,0);
	rc_servo(2,0);
	
	// Set prescaler to 8 and start TIMER4
	TCCR4B |=_BV(CS41);
	
	USART_putstring("\nafter: rc-servoc.c init_rc_servo()\r\n");
}

/* ======================================================================================================================= */
/**
  @brief       Set the specified servo to a given position.
 
  @param[in]  id the servo to set the position for [0..2].
  @param[in]  position to set the servo to. [-100..100]\n
			   -100: max CCW position.\n
			   0: mid position\n
			   100: max CW position.
 
  @section Description
  Calculates the correct OC4x value to be set in timer register, to give the needed pulse width.
 */
void rc_servo(uint8_t id, int8_t position)
{
	uint16_t _oc_value = 0;
	// Control of position parameter
	if (position < -100)
	{
		position = -100;
	} 
	
	if ( position > 100 )
	{
		position = 100;
	}
	
	// Calculate new OCR4x register value
	_oc_value = (int16_t)(6.24975*position +1874.925);
		
	// Set value in correct register
	switch(id)
	{
		case 0:
		OCR4A = _oc_value;
		break;
		
		case 1:
		OCR4B = _oc_value;
		break;
		
		case 2:
		OCR4C = _oc_value;		
		break;
		
		default:
		;
		// Do nothing
	}
}